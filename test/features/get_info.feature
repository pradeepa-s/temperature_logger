Feature: API to read the information about the temperature logger device

    @version.1
    Scenario: Shall receive the version information through the get info command
        Given the temperature logger is running
        When the get info command is sent and responded
        Then the responded version shall be "1.00"
