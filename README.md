nrf51-dfu-ble-S130
==================

Dual Bank DFU over BLE (nRF51, S130 alpha 0.9)

Based on the dual bank BLE bootloader example in SDKv6.1

Modification added to make the example works with S130 alpha 0.9:

- Use API include headers from S130 (the "include" folder).

- Remove m_sec_param.timeout 

- Update sd_ble_gap_sec_params_reply()

- Updated IRAM1 location and size

Softdevice & bootloader update is supported

The example was made to support debugging (optimization level set to 0 ), the bootloader address was moved down to cope with the bigger size of the bootloader when compiling without optimization. 

Tested with Android nRFToolbox, nRFMaster Control Panel

Requirements
------------
- nRF51 SDK version 6.1
- S130 v0.9 alpha
- nRF51822 Development Kit version 2.1.0 or later

The project may need modifications to work with other versions or other boards. 

To compile it, clone the repository in the \nrf51822\Board\nrf6310\device_firmware_updates folder.

About this project
------------------
This application is one of several applications that has been built by the support team at Nordic Semiconductor, as a demo of some particular feature or use case. It has not necessarily been thoroughly tested, so there might be unknown issues. It is hence provided as-is, without any warranty. 

However, in the hope that it still may be useful also for others than the ones we initially wrote it for, we've chosen to distribute it here on GitHub. 

The application is built to be used with the official nRF51 SDK, that can be downloaded from https://www.nordicsemi.no, provided you have a product key for one of our kits.

Please post any questions about this project on https://devzone.nordicsemi.com.
