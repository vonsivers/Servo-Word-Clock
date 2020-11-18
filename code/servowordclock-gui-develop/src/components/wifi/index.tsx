import { FunctionalComponent, h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import TextField from "preact-material-components/TextField";
import "preact-material-components/TextField/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/Theme/style.css";
import { route } from "preact-router";
import Constants from "../../Constants";
import { SWCClient } from "../../domain/SWCClient";

class Wifi extends Component<Props, State> {
    onClickSave(): void {
        console.log("save"); //TODO: Save => https://material.preactjs.com/component/linear-progress/
        route(Constants.routes.Home);
    }

    render() {
        return (
            <div class={style.wifi}>
                <h1>Wifi</h1>
                <div>
                    <label htmlFor="ssid">SSID</label>
                    <TextField
                        id="ssid"
                        label="SSID"
                        helperText="Your network name"
                        class={style.full}
                    />
                </div>
                <div>
                    <label htmlFor="password">Password</label>
                    <TextField
                        id="password"
                        label="Password"
                        helperText="Your network password"
                        class={style.full}
                    />
                </div>
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickSave()}>
                        Save &amp; Restart
                    </Button>
                </div>
            </div>
        );
    }
}

interface State {
    isLoading: boolean;
}
interface Props {
    client: SWCClient;
}

export default Wifi;
