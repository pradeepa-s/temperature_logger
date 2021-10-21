import subprocess

class STLinkUtils:
    def __init__(self):
        pass

    def reset():
        out = subprocess.run(["ST-LINK_CLI.exe", "-c", "SWD", "-HardRst", "PULSE=200"], capture_output=True)
        assert out.returncode == 0, "ST-LINK error"
