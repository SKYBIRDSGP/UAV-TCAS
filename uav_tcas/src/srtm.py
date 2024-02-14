# SRTM DATA EXTRACTION:
def get_sample(filename, n, e):
    i = 1201 - int(round(n / 3, 0))
    j = int(round(e / 3, 0))
    with open(filename, "rb") as f:
        f.seek(((i - 1) * 1201 + (j - 1)) * 2)  # go to the right spot,
        buf = f.read(2)  # read two bytes and convert them:
        val = struct.unpack('>h', buf)  # ">h" is a signed two byte integer
        if not val == -32768:  # the not-a-valid-sample value
            return val
        else:
            return None

if __name__ == "__main__":
    # elevation at 18°27'17.0"N 73°55'22.1"E
    n = 27 * 60 + 0
    e = 55 * 60 + 22.1
    tile = "/home/sagar/Desktop/UAV-Avionics/srtm data/N18E073.hgt"
    print(get_sample(tile, n, e))