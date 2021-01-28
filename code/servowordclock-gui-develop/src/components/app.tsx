import { h, Component } from "preact";
import { route, Router } from "preact-router";

import Constants from "../Constants";
import Home from "./home";
import Wifi from "./wifi";
import Display from "./display";
import NightMode from "./night-mode";
import TimeSettings from "./time-settings";
import Header from "./header";
import { createHashHistory } from "history";
import { SWCClient } from "../domain/SWCClient";
import { Auth } from "../domain/apiUtils";
import Login from "./login";

// eslint-disable-next-line @typescript-eslint/no-explicit-any
if ((module as any).hot) {
    // tslint:disable-next-line:no-var-requires
    require("preact/debug");
}

class App extends Component<Props, State> {
    state: State = {
        currentRoute: Constants.routes.Login,
        auth: {
            key: "",
            onNoAuth: () => route(Constants.routes.Login)
        }
    };
    client = new SWCClient(this.state.auth);

    render() {
        return (
            <div id="app">
                <Header currentRoute={this.state.currentRoute} />
                <Router
                    onChange={e => this.setState({ currentRoute: e.url })}
                    history={createHashHistory()}
                >
                    <Home path={Constants.routes.Home} client={this.client} />
                    <Wifi path={Constants.routes.Wifi} client={this.client} />
                    <TimeSettings
                        path={Constants.routes.TimeSettings}
                        client={this.client}
                    />
                    <Display
                        path={Constants.routes.Display}
                        client={this.client}
                    />
                    <NightMode
                        path={Constants.routes.NightMode}
                        client={this.client}
                    />
                    <Login default client={this.client} />
                </Router>
            </div>
        );
    }
}

interface State {
    currentRoute: string;
    auth: Auth;
}
// eslint-disable-next-line @typescript-eslint/no-empty-interface
interface Props {}

export default App;
