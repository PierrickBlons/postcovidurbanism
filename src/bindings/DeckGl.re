module Layers = {
  type t;

  module Line = {
    type position = (float, float);
    type data = {
      label: string,
      description: string,
      sourcePosition: position,
      targetPosition: position,
      kind: string,
      authorName: string,
    };
    type info = {
      [@bs.as "object"]detail: data,
      x: int,
      y: int
    }
    type obj = {
      id: string,
      data: array(data),
      getColor: data => (int, int, int, int),
      getWidth: int,
      onClick: info => unit,
      pickable: bool
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
    "StaticMap";
};
