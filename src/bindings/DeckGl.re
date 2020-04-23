module Layers = {
  type t;

  module GeoJson = {

    type property = {
      label: string,
      description: string,
      kind: string,
      authorName: string,
      authorLink: string,
    };

    type feature = {
      [@bs.as "type"]_type: string,
      geometry: Js.Json.t,
      properties: property,
    };

    type geojson = {
      [@bs.as "type"]_type: string,
      version: string,
      features: array(feature),
    }

    type info = {
      [@bs.as "object"]feature: feature,
      x: int,
      y: int
    }

    type obj = {
      id: string,
      data: geojson,
      pickable: bool,
      getLineColor: feature => (int, int, int, int),
      getLineWidth: int,
      onClick: info => unit,
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
