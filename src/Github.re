open Fetch;

type user = {
  login: string,
  name: string,
  html_url: string
};

let users = (login: string, callback) =>
  Js.Promise.(
    fetch("https://api.github.com/users/" ++ login)
    |> then_(Response.json)
    |> then_(json => {
      let user = Json.Decode.{
        login: json |> field("login", string),
        name: json |> field("name", string),
        html_url: json |> field("html_url", string)
      };
      callback(user);
      resolve();
    })
  );
