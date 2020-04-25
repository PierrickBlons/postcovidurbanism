type author = {
  name: string,
  link: option(string),
};

type proposal = {
  title: string,
  startLatitude: option(float),
  startLongitude: option(float),
  endLatitude: option(float),
  endLongitude: option(float),
  description: option(string),
  kind: string,
  path: option(DeckGl.Layers.GeoJson.geometry),
  author: option(author),
};