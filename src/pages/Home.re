open DeckGl.Layers.GeoJson;

let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let layerLineId = "layer-id";
let lineWidth: int = 7;
let linePedestrianColor: (int, int, int, int) = (36, 142, 128, 255);
let lineCyclingColor: (int, int, int, int) = (0, 128, 255, 200);
let lineSchoolColor: (int, int, int, int) = (255, 191, 0, 255);

let getColor = kind =>
  switch (kind) {
  | "pieton" => linePedestrianColor
  | "velo" => lineCyclingColor
  | "ecole" => lineSchoolColor
  | _ => (0, 0, 0, 0)
  };

type state = {
  label: string,
  visible: bool,
  description: string,
  authorName: string,
  authorLink: string,
};

type action =
  | Click(info);

let initialState = {
  label: "Urbanisme tactique post covid",
  description: {j|Sélectionner un élément de la cartographie pour faire apparaitre le détail de la proposition|j},
  visible: true,
  authorName: "",
  authorLink: "",
};

[@react.component]
let make = () => {
  let (proposals, _) = Queries.useProposalsListQuery();

  let (state, dispatch) =
    React.useReducer(
      (_, action) => {
        switch (action) {
        | Click(info) => {
            label: info.feature.properties.label,
            description: info.feature.properties.description,
            visible: true,
            authorName: info.feature.properties.authorName,
            authorLink: info.feature.properties.authorLink,
          }
        };
      },
      initialState,
    );

  let defaultFeature = {
    _type: "Feature",
    geometry: Js.Json.parseExn({js|{"type": "LineString"}|js}),
    properties: {
      label: "",
      description: "",
      kind: "",
      authorLink: "",
      authorName: "",
    },
  };

  let geojsonLine =
      (startlatitude: float, startlongitude, endlatitude, endlongitude) =>
    "{\"type\": \"LineString\", \"coordinates\": [ ["
    ++ Js.Float.toString(startlatitude)
    ++ ","
    ++ Js.Float.toString(startlongitude)
    ++ "],["
    ++ Js.Float.toString(endlatitude)
    ++ ","
    ++ Js.Float.toString(endlongitude)
    ++ "] ]}";

  let extractFloat = someFloat =>
    Js.Json.decodeNumber(someFloat)->Belt.Option.getWithDefault(0.);

  let data: geojson = {
    _type: "FeatureCollection",
    version: "draft",
    features:
      switch (proposals) {
      | Data(data) =>
        data##proposal
        ->Belt.Array.map(proposal => {
            switch (
              proposal##path,
              proposal##startLatitude,
              proposal##startLongitude,
              proposal##endLatitude,
              proposal##endLongitude,
            ) {
            | (Some(path), None, None, None, None) => {
                _type: "Feature",
                geometry: path,
                properties: {
                  label: proposal##title,
                  description:
                    proposal##description->Belt.Option.getWithDefault(""),
                  kind: proposal##kind,
                  authorLink:
                    proposal##author
                    ->Belt.Option.mapWithDefault("", author =>
                        author##link->Belt.Option.getWithDefault("")
                      ),
                  authorName:
                    proposal##author
                    ->Belt.Option.mapWithDefault("", author => author##name),
                },
              }
            | (
                None,
                Some(startlatitude),
                Some(startlongitude),
                Some(endlatitude),
                Some(endlongitude),
              ) => {
                _type: "Feature",
                geometry:
                  Js.Json.parseExn(
                    geojsonLine(
                      extractFloat(startlongitude),
                      extractFloat(startlatitude),
                      extractFloat(endlongitude),
                      extractFloat(endlatitude),
                    ),
                  ),
                properties: {
                  label: proposal##title,
                  description:
                    proposal##description->Belt.Option.getWithDefault(""),
                  kind: proposal##kind,
                  authorLink:
                    proposal##author
                    ->Belt.Option.mapWithDefault("", author =>
                        author##link->Belt.Option.getWithDefault("")
                      ),
                  authorName:
                    proposal##author
                    ->Belt.Option.mapWithDefault("", author => author##name),
                },
              }
            | _ => defaultFeature
            }
          })
      | _ => [||]
      },
  };

  let layers = [|
    create({
      id: layerLineId,
      data,
      pickable: true,
      getLineColor: feature => getColor(feature.properties.kind),
      getLineWidth: 12,
      onClick: feature => dispatch(Click(feature)),
    }),
  |];

  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/dark-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
    <Tooltip
      isVisible={state.visible}
      label={state.label}
      description={state.description}
      authorName={state.authorName}
      authorLink={state.authorLink}
    />
  </DeckGl>;
};
