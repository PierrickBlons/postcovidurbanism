module Layers = {
  type t;

  module Line = {
    type coordinates = array(float);
    type geometry = {
      [@bs.as "type"]_type: string,
      coordinates: array(coordinates),
    }

    type feature = {
      [@bs.as "type"]_type: string,
      geometry: geometry,
    }

    type geojson = {
      [@bs.as "type"]_type: string,
      version: string,
      features: array(feature),
    }

    // type data = {
    //   label: string,
    //   description: string,
    //   sourcePosition: position,
    //   targetPosition: position,
    //   kind: string,
    //   authorName: string,
    //   authorLink: string,
    // // };
    // type info = {
    //   [@bs.as "object"]detail: geojson,
    //   x: int,
    //   y: int
    // }
    type obj = {
      id: string,
      data: Js.Json.t,
      getLineColor: unit => (int, int, int, int),
      pickable: bool,
    };
    
    [@bs.module "@deck.gl/layers"] [@bs.new]
    external create: obj => t = "GeoJsonLayer";
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
