import os
import struct
import zlib

ignore_list = [".DS_Store"]
root_name = "assets"

assets_table = []

with open("../cmake-build-debug/game.dat", 'wb') as write_stream:
    table_length = 0

    file_header = b"\x00\x00\x00\x00" * 8

    write_stream.write(file_header)

    for root, ds, fs in os.walk(root_name):
        for f in fs:
            full_name = os.path.join(root, f)
            if not f in ignore_list:
                file_name, ext = os.path.splitext(f)
                _index = os.path.dirname(full_name[len(root_name):]).replace("\\", "/")
                _name = f"{_index}/{file_name}"
                _type = ext[1:]
                _origin_size = os.path.getsize(full_name)
                _pointer = write_stream.tell()
                with open(full_name, 'rb') as read_stream:
                    content = read_stream.read()
                    compressed_content = zlib.compress(content)
                    _compressed_size = len(compressed_content)
                    write_stream.write(compressed_content)
                temp = {"name": _name,
                        "type": _type,
                        "pointer": _pointer,
                        "name_pointer": 0,
                        "compressed_size": _compressed_size,
                        "origin_size": _origin_size}
                table_length += _compressed_size
                assets_table.append(temp)

    string_table = bytes()
    length_before = 0

    for asset in assets_table:
        asset["name_pointer"] = length_before
        string_table += (asset["name"] + "\x00").encode()
        length_before += len(asset["name"]) + 1

    buffer = zlib.compress(string_table)
    string_table_origin_size = len(string_table)
    string_table_compressed_size = len(buffer)
    string_table_pointer = write_stream.tell()
    write_stream.write(buffer)

    assests_table_header = bytes()

    for asset in assets_table:
        temp = struct.pack("<L", asset["pointer"]) + struct.pack("<L", asset["origin_size"]) + struct.pack(
            "<L", asset["compressed_size"]) + struct.pack("<L", asset["name_pointer"]) + asset[
                   "type"].encode() + b"\x00"
        assests_table_header += temp

    buffer = zlib.compress(assests_table_header)
    assests_table_header_origin_size = len(assests_table_header)
    assests_table_header_compressed_size = len(buffer)
    assests_table_header_pointer = write_stream.tell()
    write_stream.write(buffer)

    write_stream.seek(0, 0)
    write_stream.write(b"GDAT")
    write_stream.write(struct.pack("<L", len(assets_table)))

    write_stream.write(struct.pack("<L", string_table_pointer))
    write_stream.write(struct.pack("<L", string_table_origin_size))
    write_stream.write(struct.pack("<L", string_table_compressed_size))

    write_stream.write(struct.pack("<L", assests_table_header_pointer))
    write_stream.write(struct.pack("<L", assests_table_header_origin_size))
    write_stream.write(struct.pack("<L", assests_table_header_compressed_size))
    write_stream.seek(0, 2)
