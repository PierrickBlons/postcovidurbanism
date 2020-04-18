[@react.component]
let make = () =>
  <ApolloHooks.Provider client=GraphqlClient.instance>
    <App />
  </ApolloHooks.Provider>;