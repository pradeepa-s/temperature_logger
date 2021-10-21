import sys
from os.path import dirname
sys.path.append('..')

from test_support.temperature_logger import device
from test_support.stlink_utils import STLinkUtils

def before_feature(context, feature):
    STLinkUtils.reset()
    context.device = device()
