{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "addon",
      "sources": [
        "Process.cc"
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