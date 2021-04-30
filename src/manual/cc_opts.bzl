"cc_binary opts for all benchmark rules"

COPTS = [
    "-Ofast",
    "-std=c++2a",
    "-march=native",
    "-DNDEBUG",
]
