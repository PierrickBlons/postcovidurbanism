let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 10,
  pitch: 0,
  bearing: 0,
};

let layerLineId = "layer-id";
let lineWidth: int = 7;
let linePedestrianColor: (int, int, int, int) = (36, 142, 128, 255);
let lineCyclingColor: (int, int, int, int) = (0, 128, 255, 200);
let lineSchoolColor: (int, int, int, int) = (255, 191, 0, 255);

let getColor = (kind) => 
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
};

type action =
  | Click(DeckGl.Layers.Line.info);

let initialState = {
  label: "Urbanisme tactique post covid",
  description: {j|Sélectionner un élément de la cartographie pour faire apparaitre le détail de la proposition|j},
  visible: true,
};

[@react.component]
let make = () => {
  let (proposals, _) = Queries.useProposalsListQuery();

  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | Click(info) => {
            label: info.detail.label,
            description: info.detail.description,
            visible: true,
          }
        },
      initialState,
    );

  let data =
    switch (proposals) {
    | Data(data) =>
      data##proposal
      ->Belt.Array.map(proposal => {
          switch (
            proposal##startLatitude,
            proposal##startLongitude,
            proposal##endLatitude,
            proposal##endLongitude,
          ) {
          | (
              Some(startLatitude),
              Some(startLongitude),
              Some(endLatitude),
              Some(endLongitude),
            ) => {
              DeckGl.Layers.Line.label: proposal##title,
              DeckGl.Layers.Line.kind: proposal##kind,
              DeckGl.Layers.Line.description:
                proposal##description->Belt.Option.getWithDefault(""),
              DeckGl.Layers.Line.sourcePosition: (
                Js.Json.decodeNumber(startLongitude)
                ->Belt.Option.getWithDefault(0.),
                Js.Json.decodeNumber(startLatitude)
                ->Belt.Option.getWithDefault(0.),
              ),
              DeckGl.Layers.Line.targetPosition: (
                Js.Json.decodeNumber(endLongitude)
                ->Belt.Option.getWithDefault(0.),
                Js.Json.decodeNumber(endLatitude)
                ->Belt.Option.getWithDefault(0.),
              ),
            }
          | _ => {
              label: "",
              kind: "",
              description: "",
              sourcePosition: (0., 0.),
              targetPosition: (0., 0.),
            }
          }
        })
    | _ => [||]
    };

  let layers = [|
    DeckGl.Layers.Line.create({
      id: layerLineId,
      data,
      getColor: d => getColor(d.kind),
      getWidth: lineWidth,
      onClick: info => dispatch(Click(info)),
      pickable: true,
    }),
  |];

  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/dark-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
    <Tooltip isVisible=state.visible label=state.label description=state.description />
  </DeckGl>;
};
