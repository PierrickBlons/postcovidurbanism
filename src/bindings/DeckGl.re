module Layers = {
  type t;

  module GeoJson = {
    type color = (int, int, int, int);

    [@decco]
    type latitude = float;
    [@decco]
    type longitude = float;

    type property = {
      label: string,
      description: string,
      kind: string,
      authorName: string,
      authorLink: string,
    };

    [@decco]
    type geometry = {
      [@decco.key "type"] [@bs.as "type"]
      _type: string,
      // Why do we have an extra value ?
      coordinates: array((longitude, latitude, float)),
    };
    type feature = {
      [@bs.as "type"]
      _type: string,
      geometry,
      properties: property,
    };

    let defaultFeature = {
      _type: "Feature",
      geometry: {
        _type: "LineString",
        coordinates: [||],
      },
      properties: {
        label: "",
        description: "",
        kind: "",
        authorLink: "",
        authorName: "",
      },
    };

    type geojson = {
      [@bs.as "type"]
      _type: string,
      version: string,
      features: array(feature),
    };

    type info = {
      [@bs.as "object"]
      feature,
      x: int,
      y: int,
    };

    type obj = {
      id: string,
      data: geojson,
      pickable: bool,
      getLineColor: feature => color,
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
