Feature: Basic temperature logging shall work

    @logging-1
    Scenario: Temperature shall log every one minute when configured
        Given temperature logging interval is set to "1" minute
        When the device had run for "1" minute
        Then device shall contain one temperature reading
