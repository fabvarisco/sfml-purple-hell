{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gnumake
  ];

  buildInputs = with pkgs; [
    sfml_2 # o projeto usa API da SFML 2.5; pkgs.sfml é a 3.x, incompatível
  ];
}
