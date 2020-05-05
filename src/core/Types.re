type boundaries('a) = {
  min: 'a,
  max: 'a,
};

type boundaryBox('a, 'b) = {
  longitudeBoundaries: boundaries('a),
  latitudeBoundaries: boundaries('b),
};

module type Coordinate = {
  [@decco]
  type latitude;
  [@decco]
  type longitude;
  [@decco]
  type altitude;
  [@decco]
  type t = (longitude, latitude, altitude);

  let latitude_from_float: float => latitude;
  let longitude_from_float: float => longitude;
  let altitude_from_float: float => altitude;

  let isValid: (boundaryBox(longitude, latitude), t) => bool;
};

module Coordinate: Coordinate = {
  [@decco]
  type latitude = float;
  [@decco]
  type longitude = float;
  [@decco]
  type altitude = float;
  [@decco]
  type t = (longitude, latitude, altitude);

  let latitude_from_float = lat => lat;
  let longitude_from_float = lat => lat;
  let altitude_from_float = lat => lat;

  let isValid =
      ({longitudeBoundaries, latitudeBoundaries}, (longitude, latitude, _)) => {
    switch (
      longitudeBoundaries.max > longitude,
      longitudeBoundaries.min < longitude,
      latitudeBoundaries.max > latitude,
      latitudeBoundaries.min < latitude,
    ) {
    | (true, true, true, true) => true
    | _ => false
    };
  };
};

[@decco]
type geometry = {
  [@decco.key "type"] [@bs.as "type"]
  _type: string,
  coordinates: array(Coordinate.t),
};

type author = {
  name: string,
  link: option(string),
};

type proposal = {
  title: string,
  startLatitude: option(Coordinate.latitude),
  startLongitude: option(Coordinate.longitude),
  endLatitude: option(Coordinate.latitude),
  endLongitude: option(Coordinate.longitude),
  description: option(string),
  kind: string,
  path: option(geometry),
  author: option(author),
};
