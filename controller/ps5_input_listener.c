#include <IOKit/IOKitLib.h>          // For IOServiceMatching
#include <IOKit/hid/IOHIDManager.h>   // For IOHIDManager and HID-related functions
#include <CoreFoundation/CoreFoundation.h>   // For CoreFoundation types
#include <stdio.h>

#define kHIDUsage_Dig_ContactID 0x51  // Contact ID usage from HID Digitizer page
#define kHIDUsage_Dig_X 0x30   // X-axis for digitizer/touchpad input
#define kHIDUsage_Dig_Y 0x31   // Y-axis for digitizer/touchpad input


// Callback function to handle incoming input reports
void handleInputReport(void* context, IOReturn result, void* sender, IOHIDReportType type, uint32_t reportID, uint8_t* report, CFIndex reportLength) {
    // Check if the report contains gyroscope data
    if (reportID == 0x31) {  // Assuming 0x31 is the report ID for motion data
        // Extract gyroscope data from the report
        int16_t gyroX = (report[13] << 8) | report[12];  // Example indices for gyro X data
        int16_t gyroY = (report[15] << 8) | report[14];  // Example indices for gyro Y data
        int16_t gyroZ = (report[17] << 8) | report[16];  // Example indices for gyro Z data

        // Print the gyroscope values
        printf("Gyro X: %d, Gyro Y: %d, Gyro Z: %d\n", gyroX, gyroY, gyroZ);
    }
}

// Callback function to detect button presses, joystick movements, and touchpad events
void HIDInputCallback(void* context, IOReturn result, void* sender, IOHIDValueRef value) {
    IOHIDElementRef element = IOHIDValueGetElement(value);

    // Get the usage page and usage to identify the type of input (button, axis, touchpad, etc.)
    uint32_t usagePage = IOHIDElementGetUsagePage(element);
    uint32_t usage = IOHIDElementGetUsage(element);


    // Process button presses (on usage page 0x09 for gamepads)
    if (usagePage == kHIDPage_Button) {
        int state = IOHIDValueGetIntegerValue(value);
        printf("Button %d: %s\n", usage, state ? "Pressed" : "Released");
        //printf("usagePage: %u\n\n\n", usagePage);

    }
    // Process joystick movements (on usage page 0x01 for generic desktop controls)
    else if (usagePage == kHIDPage_GenericDesktop) {
        int axisValue = IOHIDValueGetIntegerValue(value);
        switch (usage) {
            case kHIDUsage_GD_X:  // X-axis (left-right movement)
                printf("Joystick X-axis: %d\n", axisValue);
                break;
            case kHIDUsage_GD_Y:  // Y-axis (up-down movement)
                printf("Joystick Y-axis: %d\n", axisValue);
                break;
            default:
                printf("Unknown joystick axis: %d, value: %d\n", usage, axisValue);
                break;
        }
        //printf("usagePage: %u\n\n\n", usagePage);

    }
    // Process touchpad inputs (on usage page 0x0D for digitizers)
    else if (usagePage == kHIDPage_Digitizer) {
        int touchValue = IOHIDValueGetIntegerValue(value);
        switch (usage) {
            case kHIDUsage_Dig_TouchScreen:  // Touchscreen event
                printf("Touchpad touched: %d\n", touchValue);
                break;
            case kHIDUsage_Dig_ContactID:    // Contact ID (which finger)
                printf("Touchpad contact ID: %d\n", touchValue);
                break;
            case kHIDUsage_Dig_X:            // X-axis of touch
                printf("Touchpad X-axis: %d\n", touchValue);
                break;
            case kHIDUsage_Dig_Y:            // Y-axis of touch
                printf("Touchpad Y-axis: %d\n", touchValue);
                break;
            default:
                printf("Unknown touchpad event: %d, value: %d\n", usage, touchValue);
                break;
        }
        //printf("usagePage: %u\n\n\n", usagePage);
    }
}

// Function to set up HID Manager and device matching
IOHIDManagerRef setupHIDManager() {
    // Create HID Manager
    IOHIDManagerRef hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);

    // Create a dictionary to match only the PS5 controller (or other gamepad by Vendor/Product ID)
    CFMutableDictionaryRef matchingDict = IOServiceMatching("IOHIDDevice");

    // Set device matching criteria: Sony PS5 Controller (VendorID: 0x054C, ProductID: 0x0CE6)
    CFNumberRef vendorID = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, (int[]){0x054C});  // Sony
    CFNumberRef productID = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, (int[]){0x0CE6}); // PS5 Controller

    CFDictionarySetValue(matchingDict, CFSTR(kIOHIDVendorIDKey), vendorID);
    CFDictionarySetValue(matchingDict, CFSTR(kIOHIDProductIDKey), productID);

    // Set the matching dictionary to the HID Manager
    IOHIDManagerSetDeviceMatching(hidManager, matchingDict);

    // Release dictionary and other objects
    CFRelease(vendorID);
    CFRelease(productID);
    CFRelease(matchingDict);

    // Open the HID Manager
    IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone);

    return hidManager;
}


IOHIDDeviceRef getPS5Controller(IOHIDManagerRef hidManager) {
    CFSetRef deviceSet = IOHIDManagerCopyDevices(hidManager);
    if (deviceSet == NULL) {
        printf("No HID devices found.\n");
        return NULL;
    }

    // Iterate through the device set to find the PS5 controller
    CFIndex deviceCount = CFSetGetCount(deviceSet);
    IOHIDDeviceRef devices[deviceCount];
    CFSetGetValues(deviceSet, (const void **)devices);

    for (CFIndex i = 0; i < deviceCount; i++) {
        IOHIDDeviceRef device = devices[i];
        CFNumberRef vendorIDRef = IOHIDDeviceGetProperty(device, CFSTR(kIOHIDVendorIDKey));
        CFNumberRef productIDRef = IOHIDDeviceGetProperty(device, CFSTR(kIOHIDProductIDKey));

        int vendorID = 0;
        int productID = 0;
        CFNumberGetValue(vendorIDRef, kCFNumberIntType, &vendorID);
        CFNumberGetValue(productIDRef, kCFNumberIntType, &productID);

        if (vendorID == 0x054C && productID == 0x0CE6) {
            printf("PS5 controller found!\n");
            CFRelease(deviceSet);
            return device;  // Return the reference to the PS5 controller
        }
    }

    printf("PS5 controller not found.\n");
    CFRelease(deviceSet);
    return NULL;
}

int main() {
    // Set up HID Manager
    IOHIDManagerRef hidManager = setupHIDManager();
    if (!hidManager) {
        printf("Error: Failed to create HID Manager.\n");
        return -1;
    }


    // Register input value callback
    IOHIDManagerRegisterInputValueCallback(hidManager, HIDInputCallback, NULL);

    // Schedule the HID manager on the run loop
    IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    // Get the PS5 controller device reference
    IOHIDDeviceRef device = getPS5Controller(hidManager);

    IOHIDDeviceRegisterInputReportCallback(device, (uint8_t*)malloc(64), 64, handleInputReport, NULL);


    // Start the run loop to listen for button presses, joystick movements, and touchpad inputs
    printf("Listening for button presses, joystick movements, and touchpad inputs...\n");
    CFRunLoopRun(); // This will block and keep listening for input events

    // Clean up
    IOHIDManagerClose(hidManager, kIOHIDOptionsTypeNone);
    CFRelease(hidManager);

    return 0;
}
