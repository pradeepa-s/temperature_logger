Feature: Device reset api and power on notification

    @reset.1
    Scenario: Shall recieve power on notification upon power on
        Given the temperature logger is switched off
        When the temperature logger is switched on
        Then the temperature logger will send the power on notification

    @reset.2
    Scenario: Reset command shall reset the device
        Given the temperature logger is running
        When the temperature logger reset command is sent
        Then the temperature logger will send the power on notification
