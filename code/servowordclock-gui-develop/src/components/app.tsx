import { h, Component } from "preact";
import { Router } from "preact-router";

import Constants from "../Constants";
import Home from "./home";
import Wifi from "./wifi";
import Display from "./display";
import NightMode from "./night-mode";
import TimeSettings from "./time-settings";
import NotFoundPage from "./notfound";
import Header from "./header";
import { createHashHistory } from "history";
import {
    SWCClient,
    NightModeSettings,
    DisplayEffectsSettings
} from "../domain/SWCClient";
import LinearProgress from "preact-material-components/LinearProgress";
import "preact-material-components/LinearProgress/style.css";
import { Auth } from "../domain/apiUtils";

// eslint-disable-next-line @typescript-eslint/no-explicit-any
if ((module as any).hot) {
    // tslint:disable-next-line:no-var-requires
    require("preact/debug");
}

class App extends Component<Props, State> {
    state: State = {
        currentRoute: Constants.routes.Home,
        auth: {
            login: "114servos",
            onNoAuth: () => alert("no auth")
        }
    };
    client = new SWCClient(this.state.auth);

    componentDidMount() {
		
        this.client
            .getDisplayEffectsSettings()
            .then(displayEffectsSettings =>
                this.setState({ displayEffectsSettings })
            );
        this.client
            .getNightModeSettings()
            .then(nightModeSettings => this.setState({ nightModeSettings }));
    }

    render() {
        if (
            !this.state.displayEffectsSettings ||
            !this.state.nightModeSettings
        ) {
            return (
                <div>
                    <LinearProgress indeterminate />
                </div>
            );
        }

        return (
            <div id="app">
                <Header currentRoute={this.state.currentRoute} />
                <Router
                    onChange={e => this.setState({ currentRoute: e.url })}
                    history={createHashHistory()}
                >
                    <Home path={Constants.routes.Home} />
                    <Wifi path={Constants.routes.Wifi} client={this.client} />
                    <TimeSettings
                        path={Constants.routes.TimeSettings}
                        client={this.client}
                    />
                    <Display
                        path={Constants.routes.Display}
                        client={this.client}
                        settings={this.state.displayEffectsSettings}
                    />
                    <NightMode
                        path={Constants.routes.NightMode}
                        client={this.client}
                        settings={this.state.nightModeSettings}
                    />
                    <NotFoundPage default />
                </Router>
            </div>
        );
    }
}

interface State {
    nightModeSettings?: NightModeSettings;
    displayEffectsSettings?: DisplayEffectsSettings;
    currentRoute: string;
    auth: Auth
}
// eslint-disable-next-line @typescript-eslint/no-empty-interface
interface Props {}

export default App;
