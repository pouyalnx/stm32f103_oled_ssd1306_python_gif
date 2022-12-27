#include <stdint.h>
#include "rl_usb.h"
 int req_counter;
 /*
 const uint8_t usbd_hid0_report_descriptor[];
const uint8_t usbd_hid0_report_descriptor[] = {
  HID_UsagePage(HID_USAGE_PAGE_GENERIC),
  HID_Usage(HID_USAGE_GENERIC_MOUSE),
  HID_Collection(HID_Application),
    HID_Usage(HID_USAGE_GENERIC_POINTER),
    HID_Collection(HID_Physical),
      HID_UsagePage(HID_USAGE_PAGE_GENERIC),
      HID_Usage(HID_USAGE_GENERIC_X),
      HID_Usage(HID_USAGE_GENERIC_Y),
      HID_LogicalMin((uint8_t)(-127)),
      HID_LogicalMax(127),
      HID_ReportSize(8),
      HID_ReportCount(2),
      HID_Input(HID_Variable | HID_Relative),
    HID_EndCollection,
  HID_EndCollection,
};

extern 
const uint8_t usbd_hid0_report_descriptor[];
const uint8_t usbd_hid0_report_descriptor[] = {
  HID_UsagePage(HID_USAGE_PAGE_GENERIC),//2
  HID_Usage(HID_USAGE_GENERIC_KEYBOARD),//2
  HID_Collection(HID_Application),//2
		HID_ReportCount(5),
		HID_ReportSize(1),
		HID_UsagePage(HID_USAGE_PAGE_LED),
      HID_LogicalMin(0),
      HID_LogicalMax(1),
		HID_UsageMin(1),
		HID_UsageMax(5),
		HID_Output(HID_Variable),
		HID_ReportCount(1),
		HID_ReportSize(3),
		HID_Output(HID_Constant|HID_Variable),
  HID_EndCollection,
};
   HID_UsagePage(HID_USAGE_PAGE_GENERIC),//2
  HID_Usage(HID_USAGE_GENERIC_KEYBOARD),//2
  HID_Collection(HID_Application),//2
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),
      HID_LogicalMin(0),
      HID_LogicalMax(1),
		HID_UsageMin(224),
		HID_UsageMax(231),
		HID_ReportCount(8),
		HID_ReportSize(1),
		HID_Input(HID_Variable),
		HID_ReportCount(1),
		HID_ReportSize(8),		
		HID_Input(HID_Constant|HID_Variable),
	   HID_ReportCount(5),
		HID_ReportSize(1),
		HID_UsagePage(HID_USAGE_PAGE_LED),
      HID_LogicalMin(0),
      HID_LogicalMax(1),
		HID_UsageMin(1),
		HID_UsageMax(5),
		HID_Output(HID_Variable),
		HID_ReportCount(1),
		HID_ReportSize(3),
		HID_Output(HID_Constant|HID_Variable),
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),
      HID_LogicalMin(0),
      HID_LogicalMax(101),
		HID_UsageMin(0),
		HID_UsageMax(101),
		HID_ReportCount(6),
		HID_ReportSize(8),
		HID_Input(0),
  HID_EndCollection,
 */
// User Provided HID Report Descriptor
// for standard mouse (size of this descriptor is 52 bytes)
extern 
const uint8_t usbd_hid0_report_descriptor[];
const uint8_t usbd_hid0_report_descriptor[] = {
 HID_UsagePage(HID_USAGE_PAGE_GENERIC),//2
  HID_Usage(HID_USAGE_GENERIC_KEYBOARD),//2
  HID_Collection(HID_Application),//2
		HID_ReportCount(5),
		HID_ReportSize(1),
		HID_UsagePage(HID_USAGE_PAGE_LED),

		HID_LogicalMin(0),
      HID_LogicalMax(1),
		HID_UsageMin(1),
		HID_UsageMax(5),
		HID_Output(HID_Variable),
		HID_ReportCount(1),
		HID_ReportSize(3),
		HID_Output(HID_Constant|HID_Variable),
  HID_EndCollection,
};
 
extern  const uint8_t usbd_hid1_report_descriptor[];
const uint8_t usbd_hid1_report_descriptor[] = {
  HID_UsagePage(HID_USAGE_PAGE_GENERIC),
  HID_Usage(HID_USAGE_GENERIC_MOUSE),
  HID_Collection(HID_Application),
    HID_Usage(HID_USAGE_GENERIC_POINTER),
    HID_Collection(HID_Physical),
      HID_UsagePage(HID_USAGE_PAGE_GENERIC),
      HID_Usage(HID_USAGE_GENERIC_X),
      HID_Usage(HID_USAGE_GENERIC_Y),
		HID_UsageMin((uint8_t)-127),
		HID_UsageMax(127), 
	   HID_LogicalMin((uint8_t)(-127)),
      HID_LogicalMax(127),
      HID_ReportSize(8),
      HID_ReportCount(2),
      HID_Input(HID_Variable | HID_Relative),
    HID_EndCollection,
  HID_EndCollection,
};

// Called during USBD_Initialize to initialize the USB HID class instance.
void USBD_HID0_Initialize (void) {
	req_counter=0;
  // Add code for initialization
}
 
 
// Called during USBD_Uninitialize to de-initialize the USB HID class instance.
void USBD_HID0_Uninitialize (void) {
  // Add code for de-initialization
}
 
 
// \brief Prepare HID Report data to send.
// \param[in]   rtype   report type:
//                - HID_REPORT_INPUT           = input report requested
//                - HID_REPORT_FEATURE         = feature report requested
// \param[in]   req     request type:
//                - USBD_HID_REQ_EP_CTRL       = control endpoint request
//                - USBD_HID_REQ_PERIOD_UPDATE = idle period expiration request
//                - USBD_HID_REQ_EP_INT        = previously sent report on interrupt endpoint request
// \param[in]   rid     report ID (0 if only one report exists).
// \param[out]  buf     buffer containing report data to send.
// \return              number of report data bytes prepared to send or invalid report requested.
//              - value >= 0: number of report data bytes prepared to send
//              - value = -1: invalid report requested

extern char key_data[2];
int32_t USBD_HID1_GetReport (uint8_t rtype, uint8_t req, uint8_t rid, uint8_t *buf) {

  buf[0] = key_data[0];       // Data Value = 0
  buf[2] = key_data[1];       // Data Value = 5
  return (2);       // Data Size  = 2 bytes	
	
  switch (rtype) {
    case HID_REPORT_INPUT:
      switch (rid) {
        case 0:
          switch (req) {
            case USBD_HID_REQ_EP_CTRL:        // Explicit USB Host request via Control OUT Endpoint
            case USBD_HID_REQ_PERIOD_UPDATE:  // Periodic USB Host request via Interrupt OUT Endpoint
              // Update buffer for report data, example:

              
				break;
 
            case USBD_HID_REQ_EP_INT:         // Called after USBD_HID_GetReportTrigger to signal
                                              // data obtained.
              break;
 
            default:
              break;
          }
          break;
 
        default:
          break;
      }
      break;
 
    case HID_REPORT_FEATURE:
      break;
 
    default:
      break;
  }
 
  return (0);
}

 
// \brief Process received HID Report data.
// \param[in]   rtype   report type:
//                - HID_REPORT_OUTPUT    = output report received
//                - HID_REPORT_FEATURE   = feature report received
// \param[in]   req     request type:
//                - USBD_HID_REQ_EP_CTRL = report received on control endpoint
//                - USBD_HID_REQ_EP_INT  = report received on interrupt endpoint
// \param[in]   rid     report ID (0 if only one report exists).
// \param[in]   buf     buffer that receives report data.
// \param[in]   len     length of received report data.
// \return      true    received report data processed.
// \return      false   received report data not processed or request not supported.
extern char led_data;
bool USBD_HID0_SetReport (uint8_t rtype, uint8_t req, uint8_t rid, const uint8_t *buf, int32_t len) {
 
  (void)req;
  (void)rid;
  (void)buf;
  (void)len;
 
  switch (rtype) {
    case HID_REPORT_OUTPUT:
      /*
        buf: Received Data
        len: Received Data Length
      */
	if(len)		led_data=buf[0];
      break;
 
    case HID_REPORT_FEATURE:
      break;
 
    default:
      break;
  }
 
  return true;
}
 
