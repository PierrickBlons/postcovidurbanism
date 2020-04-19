
open ApolloHooks;

module GetProposalsListQuery = [%graphql {|
    query GetProposalsList { 
            proposal {
                title
                latitude
                longitude
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetProposalsListQuery.definition);