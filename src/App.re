type state = {
  fetching: bool,
  error: string,
  login: string,
  users: list(Github.user),
};

type action =
  | StartFetching
  | ShowError(string)
  | ChangeLogin(string)
  | AddUser(Github.user)
  | DeleteUser(Github.user);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,

  initialState: () => {
    fetching: false,
    error: "",
    login: "",
    users: []
  },

  reducer: (action, state) =>
    switch (action) {
    | StartFetching =>
        ReasonReact.Update({...state, error: "", fetching: true})
    | ShowError(message) =>
        ReasonReact.Update({...state, error: message, fetching: false})
    | ChangeLogin(login) =>
        ReasonReact.Update({...state, login})
    | AddUser(user) => {
        let users = [
          user,
          ...state.users
        ];
        ReasonReact.Update({...state, users, login: "", fetching: false});
      }
    | DeleteUser(user) => {
        let users = List.filter(
          (u: Github.user) => u != user,
          state.users
        );
        ReasonReact.Update({...state, users});
      }
    },

  render: (self) => {
    let {fetching, error, login, users} = self.state;

    let submit = event => {
      if (login !== "") {
        let exists = List.exists(
          (u: Github.user) => u.login === login,
          users
        );
        if (exists) {
          self.send(ShowError(login ++ " already exists"));
        } else {
          self.send(StartFetching);
          Github.users(login, user => self.send(AddUser(user))) |> ignore;
        };
      };
      ReactEventRe.Form.preventDefault(event);
    };

    let errorMessage = error === "" ?
      ReasonReact.nullElement :
      <p className=Styles.line>
        <span className=Styles.error>
          (ReasonReact.stringToElement(error))
        </span>
        <button
          _type="button"
          onClick=(_event => self.send(ShowError("")))>
          (ReasonReact.stringToElement("Close"))
        </button>
      </p>;

    let userList = List.map(
      (user: Github.user) =>
        <p key=user.login className=Styles.line>
          <a href=user.html_url>(ReasonReact.stringToElement(user.name))</a>
          <small>(ReasonReact.stringToElement(user.login))</small>
          <button onClick=(_event => self.send(DeleteUser(user)))>
            (ReasonReact.stringToElement("Delete"))
          </button>
        </p>,
      users
    );

    <div className=Styles.root(fetching)>
      <form className=Styles.line onSubmit=(submit)>
        <input
          _type="text"
          placeholder="Type github username..."
          tabIndex=0
          autoFocus=Js.true_
          value=login
          onChange=(event => {
            let login = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
            self.send(ChangeLogin(login));
          })
        />
        <button _type="submit">
          (ReasonReact.stringToElement("Add"))
        </button>
      </form>
      (errorMessage)
      (ReasonReact.arrayToElement(Array.of_list(userList)))
    </div>
  }
};
