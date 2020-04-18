let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let data: array(DeckGl.Layers.Line.data) = [|
  {
    sourcePosition: (1.0887587, 49.4391237),
    targetPosition: (1.092123, 49.4446816),
  },
  {
    sourcePosition: (1.097269, 49.445366),
    targetPosition: (1.096135, 49.443916),
  }
|];

let layerLineId = "layer-id";
let lineColor: (int, int, int) = (255, 0, 0);
let lineWidth: int = 3;

type state = {
  posX: int,
  posY: int,
  visible: bool,
};

type action = 
  | Click(DeckGl.Layers.Line.info);

let initialState = { posX: 0, posY: 0, visible: false};

let visibleToDisplay = (visible) => visible ? "block" : "none";

[@react.component]
let make = () => {

  let (state, dispatch) = React.useReducer(
    (_, action) => 
    switch(action) {
      | Click(info) => {posX: info.x, posY: info.y, visible: true }
    }, 
    initialState);

  let renderTooltip = () => { 
      <div style=ReactDOMRe.Style.make(
          ~display=state.visible->visibleToDisplay,
          ~position="absolute",
          ~top=state.posY->string_of_int++"px",
          ~left=state.posX->string_of_int++"px",
          ())>
        {React.string("Piétonisation")}
      </div>
    };

  let layers = [|DeckGl.Layers.Line.create({
    id: layerLineId, 
    data, 
    getColor: lineColor, 
    getWidth: lineWidth,
    onClick: info => dispatch(Click(info)),
    pickable: true,
    }),
  |];
  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/light-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
    { renderTooltip(); }
  </DeckGl>;
};
