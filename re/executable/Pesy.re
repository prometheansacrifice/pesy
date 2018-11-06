type mode =
  | BUILD
  | ESY_SHELL
  | NAKED;

let mode =
  switch (Sys.getenv_opt("cur__name")) {
  | Some(x) =>
    switch (Sys.getenv_opt("SHELL")) {
    | Some(y) =>
      Str.search_forward(Str.regexp("noprofile"), y, 0) != (-1) ?
        BUILD : ESY_SHELL
    | None =>
      print_endline("Warning: Weird. cur__name present but no SHELL");
      ESY_SHELL;
    }
  | None => NAKED
  };

let mode = ESY_SHELL;

Lwt_main.run(
  switch (mode) {
  | BUILD => PesyLib.build()
  | ESY_SHELL => PesyLib.genBuildFiles()
  | NAKED =>
    PesyLib.bootstrap(
      Array.length(Sys.argv) > 1 && Sys.argv[1] == "--test-mode",
    )
  },
);
