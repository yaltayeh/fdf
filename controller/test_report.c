#include <IOKit/hid/IOHIDManager.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>
#include <stdint.h>

#define PS5_VENDOR_ID 0x054C  // Sony Vendor ID
#define PS5_PRODUCT_ID 0x0CE6 // PS5 Controller Product ID

// Example HID report for configuring the adaptive triggers
uint8_t adaptive_trigger_report[48] = {
    0x31,  // Report ID for PS5 controller (0x31 is the report ID for the DualSense)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Padding bytes
    0x02, 0x02,  // L2 and R2 trigger mode (0x02: Enable feedback)
    0xFF, 0x40,  // L2 trigger resistance (0xFF: Max force, 0x40: Strength)
    0x00, 0x00,  // Padding for L2
    0x00, 0x00,  // Padding for L2
    0xFF, 0x40,  // R2 trigger resistance (0xFF: Max force, 0x40: Strength)
    0x00, 0x00,  // Padding for R2
    0x00, 0x00,  // Padding for R2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Additional padding
};

// Function to create a matching dictionary for the PS5 controller
CFDictionaryRef createMatchingDictionary() {
    CFMutableDictionaryRef matchingDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
                                                                    &kCFTypeDictionaryKeyCallBacks,
                                                                    &kCFTypeDictionaryValueCallBacks);

    int vendorID = PS5_VENDOR_ID;
    int productID = PS5_PRODUCT_ID;

    CFNumberRef vendorIDRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &vendorID);
    CFNumberRef productIDRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &productID);

    CFDictionarySetValue(matchingDict, CFSTR(kIOHIDVendorIDKey), vendorIDRef);
    CFDictionarySetValue(matchingDict, CFSTR(kIOHIDProductIDKey), productIDRef);

    CFRelease(vendorIDRef);
    CFRelease(productIDRef);

    return matchingDict;
}

// Function to send the adaptive trigger HID report to the controller
IOReturn sendAdaptiveTriggerRequest(IOHIDDeviceRef device) {
    IOReturn result = IOHIDDeviceSetReport(
        device,
        kIOHIDReportTypeOutput,  // We're sending an output report
        adaptive_trigger_report[0],  // Report ID (0x31)
        adaptive_trigger_report,  // Pointer to the report data
        sizeof(adaptive_trigger_report)  // Size of the report
    );

    if (result == kIOReturnSuccess) {
        printf("Successfully sent adaptive trigger request!\n");
    } else {
        printf("Failed to send adaptive trigger request: %x\n", result);
    }

    return result;
}

// Function to find and return the PS5 controller
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

        if (vendorID == PS5_VENDOR_ID && productID == PS5_PRODUCT_ID) {
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
    // Create HID Manager
    IOHIDManagerRef hidManager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    CFDictionaryRef matchingDict = createMatchingDictionary();
    IOHIDManagerSetDeviceMatching(hidManager, matchingDict);
    CFRelease(matchingDict);

    // Open the HID Manager
    IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeNone);

    // Get the PS5 controller device reference
    IOHIDDeviceRef device = getPS5Controller(hidManager);

    if (device != NULL) {
        // Send adaptive trigger request
        sendAdaptiveTriggerRequest(device);
    } else {
        printf("Error: PS5 controller not found.\n");
    }

    // Clean up
    IOHIDManagerClose(hidManager, kIOHIDOptionsTypeNone);
    CFRelease(hidManager);

    return 0;
}
