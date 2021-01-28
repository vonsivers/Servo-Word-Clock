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
    WifiSettings
} from "../../domain/SWCClient";
import Icon from "preact-material-components/Icon";
import LinearProgress from "preact-material-components/LinearProgress";

class Wifi extends Component<Props, State> {
    private pollSSIDsTimeoutHandle?: number;
    constructor(props: Props) {
        super(props);
        this.pollSSIDs = this.pollSSIDs.bind(this);
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

    pollSSIDs(): void {
        this.setState({ ssidsLoading: true });
        this.props.client.getWifiSettings().then(result => {
            let ssids = result;
            if (this.state.ssids) {
                ssids = { ...this.state.ssids, ...result };
            }
            delete ssids[""];
            this.setState({ ssids, ssidsLoading: false });
            this.pollSSIDsTimeoutHandle = window.setTimeout(
                this.pollSSIDs.bind(this),
                5000
            );
        });
    }

    componentDidMount() {
        this.props.client.getWifi().then(config => this.setState({ config }));
        this.pollSSIDs();
    }

    componentWillUnmount() {
        if (this.pollSSIDsTimeoutHandle) {
            window.clearTimeout(this.pollSSIDsTimeoutHandle);
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
        const networks = this.renderNetworks();

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
                {networks}
            </div>
        );
    }

    private renderNetworks(): h.JSX.Element {
        if (this.state.ssids && Object.keys(this.state.ssids).length) {
            return (
                <div>
                    <label>Found networks</label>
                    <div>
                        <table class={style.table}>
                            <thead>
                                <tr>
                                    <th>SSID</th>
                                    <th>signal strengh</th>
                                    <th>encryption</th>
                                </tr>
                            </thead>
                            {Object.keys(this.state.ssids)
                                .sort()
                                .map((ssid, i) => (
                                    <tr
                                        key={i}
                                        onClick={() =>
                                            this.setState({
                                                config: {
                                                    ...this.state.config,
                                                    ssid,
                                                    password: ""
                                                }
                                            })
                                        }
                                    >
                                        <td>{ssid}</td>
                                        <td>{this.state.ssids[ssid][0]} %</td>
                                        <td>
                                            <Icon>
                                                {this.state.ssids[ssid][1] ===
                                                "0"
                                                    ? "no_encryption"
                                                    : "lock"}
                                            </Icon>
                                        </td>
                                    </tr>
                                ))}
                        </table>
                    </div>
                </div>
            );
        } else {
            return (
                <div>
                    <i>scanning for networks...</i>
                    <LinearProgress indeterminate />
                </div>
            );
        }
    }
}

interface State {
    isLoading: boolean;
    ssidsLoading: boolean;
    config?: WifiConfig;
    ssids?: WifiSettings;
}
interface Props {
    client: SWCClient;
}

export default Wifi;
