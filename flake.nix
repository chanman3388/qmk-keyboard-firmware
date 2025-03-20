{
  description = "Nix flake for qmk";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.2405.632874.tar.gz";
  };

  outputs = {
    self,
    flake-utils,
    nixpkgs,
  }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in with pkgs; {
        devShell = mkShell {
          shellHook = ''
            export QMK_HOME="$(dirname "$(dirname "$(pwd)")")"
          '';
          buildInputs = [
            qmk
          ];
        };
      }
    );

}
