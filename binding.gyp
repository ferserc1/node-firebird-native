{
    "targets": [
        {
            "target_name": "node-firebird",
            "cflags!": [
                "-fno-rtti",
                "-fno-exceptions"
            ],
            "cflags_cc!": [
                "-fno-rtti",
                "-fno-exceptions"
            ],
            "sources": [
                "src/cpp/ibpp/all_in_one.cpp",
                "src/cpp/fbtest.cpp",
                "src/cpp/test.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "libraries":[
                "-lfbclient"
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "defines": [
                "IBPP_LINUX"
            ]
        }
    ]
}