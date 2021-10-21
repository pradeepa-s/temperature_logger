from behave import *

@given('the temperature logger is running')
def step_impl(context):
    assert context.device.is_running(), "Device is not running"

@when('the temperature logger reset command is sent')
def step_impl(context):
    context.device.reset()

@then('the temperature logger will send the power on notification')
def step_impl(context):
    assert context.device.has_reset(), "No power on notification"

@given('the temperature logger is switched off')
def step_impl(context):
    pass

@when('the temperature logger is switched on')
def step_impl(context):
    pass

@when('the get info command is sent and responded')
def step_impl(context):
    info = context.device.get_info()
    assert len(info) != 0, "Failed to receive get info response"
    context.firmware_version = info


@then('the responded version shall be "{version}"')
def step_impl(context, version):
    assert version == context.firmware_version, "Version mismatch {} vs {}".format(version, context.firmware_version)
