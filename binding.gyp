{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "addon",
      "sources": [
        "main.cpp",
        "ProcessHelper.cpp",
        "Process.cpp"
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