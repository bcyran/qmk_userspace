{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      setupScript = pkgs.writeShellApplication {
        name = "qmk-setup";
        text = "qmk --config-file ./qmk.ini clone && qmk --config-file ./qmk.ini setup";
      };
      flashLeftScript = pkgs.writeShellApplication {
        name = "qmk-flash-left";
        text = "qmk --config-file ./qmk.ini flash -kb sofle_choc -km bcyran -bl uf2-split-left";
      };
      flashRightScript = pkgs.writeShellApplication {
        name = "qmk-flash-right";
        text = "qmk --config-file ./qmk.ini flash -kb sofle_choc -km bcyran -bl uf2-split-right";
      };
    in {
      devShells.default = pkgs.mkShell {
        packages = with pkgs; [
          qmk
          setupScript
          flashLeftScript
          flashRightScript
        ];
      };
    });
}
