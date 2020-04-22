
open ApolloHooks;

module GetProposalsListQuery = [%graphql {|
    query GetProposalsList { 
            proposal {
                title
                startLatitude
                startLongitude
                endLatitude
                endLongitude
                description
                kind
                author {
                    name
                    link
                }
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetProposalsListQuery.definition);