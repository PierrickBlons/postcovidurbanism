open DeckGl.Layers.GeoJson;

let makeProperties =
    (~kind, ~description, ~author: option(Types.author), ~title)
    : DeckGl.Layers.GeoJson.property => {
  {
    label: title,
    description: description->Belt.Option.getWithDefault(""),
    kind,
    authorLink:
      author->Belt.Option.mapWithDefault("", author =>
        author.link->Belt.Option.getWithDefault("")
      ),
    authorName: author->Belt.Option.mapWithDefault("", author => author.name),
  };
};

let toCoordinates =
  fun
  | (Some(a), Some(b)) =>
    Some((a, b, Types.Coordinate.altitude_from_float(0.)))
  | _ => None;

let makeFeature = (proposal: Types.proposal) => {
  _type: "Feature",
  properties:
    makeProperties(
      ~author=proposal.author,
      ~title=proposal.title,
      ~description=proposal.description,
      ~kind=proposal.kind,
    ),
  geometry:
    switch (proposal.path) {
    | Some(path) => path
    | None =>
      let startPoint =
        (proposal.startLongitude, proposal.startLatitude)->toCoordinates;
      let endPoint =
        (proposal.endLongitude, proposal.endLatitude)->toCoordinates;

      {
        _type: "LineString",
        coordinates:
          switch (startPoint, endPoint) {
          | (Some(startPoint), Some(endPoint)) => [|startPoint, endPoint|]
          | _ => [||]
          },
      };
    },
};

let make = proposals => {
  _type: "FeatureCollection",
  version: "draft",
  features: proposals->Belt.Array.map(makeFeature),
};
