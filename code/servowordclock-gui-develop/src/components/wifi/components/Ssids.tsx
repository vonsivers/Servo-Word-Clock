import { h, Component } from "preact";
import * as style from "./Ssids.css";
import Icon from "preact-material-components/Icon";
import LinearProgress from "preact-material-components/LinearProgress";
import {
    SWCClient,
    WifiSettings
} from "../../../domain/SWCClient";

class Ssids extends Component<Props, State> {
    private pollSSIDsTimeoutHandle?: number;
    constructor(props: Props) {
        super(props);
        this.pollSSIDs = this.pollSSIDs.bind(this);
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
        this.pollSSIDs();
    }

    componentWillUnmount() {
        if (this.pollSSIDsTimeoutHandle) {
            window.clearTimeout(this.pollSSIDsTimeoutHandle);
        }
    }


    render(): h.JSX.Element {
        if (!this.state.ssids || !Object.keys(this.state.ssids).length) {
            return (
                <div>
                    <i>scanning for networks...</i>
                    <LinearProgress indeterminate />
                </div>
            );
        }
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
                                    onClick={() => this.props.onChange(ssid)}
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
    }
}
interface Props {
    client: SWCClient;
    onChange: (value: string) => void;
}
interface State {
    ssids?: WifiSettings;
    ssidsLoading: boolean;
}
export default Ssids;