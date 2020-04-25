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
let linePedestrianColor: color = (36, 142, 128, 255);
let lineCyclingColor: color = (0, 128, 255, 200);
let lineSchoolColor: color = (255, 191, 0, 255);

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
        }
      },
      initialState,
    );

  let data: geojson = {
    switch (proposals) {
    | Data(data) => GeoJsonSelector.make(data##proposal)
    | _ => GeoJsonSelector.make([||])
    };
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
