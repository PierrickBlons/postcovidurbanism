let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let authHeaders = Js.Dict.empty();
Js.Dict.set(
  authHeaders,
  "x-hasura-admin-secret",
  Js.Json.string("{xJA;O5k:(FGD'H-"),
);

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="http://postcovidurbanism.eastus.azurecontainer.io/v1/graphql",
    ~headers=Js.Json.object_(authHeaders),
    (),
  );

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
