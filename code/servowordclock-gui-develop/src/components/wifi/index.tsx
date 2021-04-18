import { h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import TextField from "preact-material-components/TextField";
import "preact-material-components/TextField/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/Theme/style.css";
import { route } from "preact-router";
import Constants from "../../Constants";
import {
    SWCClient,
    Wifi as WifiConfig,
} from "../../domain/SWCClient";
import LinearProgress from "preact-material-components/LinearProgress";
import Ssids from "./components/Ssids";

class Wifi extends Component<Props, State> {
    componentDidMount() {
        this.props.client.getWifi().then(config => this.setState({ config }));
    }

    onClickSave(): void {
        const config = this.state.config;
        if (config) {
            this.setState({ config: undefined });
            this.props.client.setWifi(config).then(() => {
                route(Constants.routes.Home);
            });
        }
    }

    render() {
        if (!this.state.config) {
            return (
                <div>
                    <LinearProgress indeterminate />
                </div>
            );
        }

        return (
            <div class={style.wifi}>
                <h1>Wifi</h1>
                <div>
                    <label htmlFor="ssid">Connection state</label>
                    <b class={style.state}>{this.state.config.state}</b>
                    <p></p>
                </div>
                <div>
                    <label htmlFor="ssid">SSID</label>
                    <TextField
                        id="ssid"
                        label="SSID"
                        helperText="Your network name"
                        class={style.full}
                        value={this.state.config.ssid}
                        onChange={e =>
                            this.setState({
                                config: {
                                    ...this.state.config,
                                    ssid: (e.target as HTMLInputElement).value
                                }
                            })
                        }
                    />
                </div>
                <div>
                    <label htmlFor="password">Password</label>
                    <TextField
                        id="password"
                        label="Password"
                        helperText="Your network password"
                        class={style.full}
                        value={this.state.config.password}
                        onChange={e =>
                            this.setState({
                                config: {
                                    ...this.state.config,
                                    password: (e.target as HTMLInputElement)
                                        .value
                                }
                            })
                        }
                    />
                </div>
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickSave()}>
                        Save &amp; Restart
                    </Button>
                </div>
                <Ssids client={this.props.client} onChange={ssid => this.setState({
                    config: {
                        ...this.state.config,
                        ssid,
                        password: ""
                    }
                })} />
            </div>
        );
    }

}

interface State {
    isLoading: boolean;
    config?: WifiConfig;
}
interface Props {
    client: SWCClient;
}

export default Wifi;
