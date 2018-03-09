{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "addon",
      "sources": [
        "src/Process.cpp",
        "src/GetCurrentProcessWorker.cpp",
        "src/Helpers.cpp"
      ],
      "msbuild_settings": {
        "ClCompile": {
          "CompileAsManaged": "true",
          "ExceptionHandling": "Async"
        }
      }
    }
  ]
}