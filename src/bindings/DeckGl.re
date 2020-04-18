module Layers = {
  type t;

  module Line = {
    type position = (float, float);
    type data = {
      sourcePosition: position,
      targetPosition: position,
    };
    type obj = {
      id: string,
      data: array(data),
      getColor: list(int),
      getWidth: int,
    };
    [@bs.module "@deck.gl/layers"] [@bs.new]
    external create: obj => t = "LineLayer";
  };
};

type viewport = {
  longitude: float,
  latitude: float,
  zoom: int,
  pitch: int,
  bearing: int,
};

[@bs.module "@deck.gl/react"] [@react.component]
external make:
  (
    ~initialViewState: viewport,
    ~controller: bool,
    ~reuseMaps: bool,
    ~layers: array(Layers.t),
    ~children: React.element
  ) =>
  React.element =
  "default";

module StaticMap = {
  [@bs.module "react-map-gl"] [@react.component]
  external make:
    (~mapboxApiAccessToken: string, ~mapStyle: string, ~viewState: viewport) =>
    React.element =
    "default";
};
