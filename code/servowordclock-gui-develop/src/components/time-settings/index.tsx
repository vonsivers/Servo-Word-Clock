import { h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import TextField from "preact-material-components/TextField";
import "preact-material-components/Button/style.css";
import "preact-material-components/TextField/style.css";
import Constants, { sanitizeTime } from "../../Constants";
import { route } from "preact-router";
import {
    SWCClient,
    TimeSettings as Config,
    TimeSettingsMode,
    TimeSettingsSettings
} from "../../domain/SWCClient";
import Checkbox from "preact-material-components/Checkbox";
import Radio from "preact-material-components/Radio";
import FormField from "preact-material-components/FormField";
import LayoutGrid from "preact-material-components/LayoutGrid";
import LinearProgress from "preact-material-components/LinearProgress";
import "preact-material-components/LinearProgress/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/Checkbox/style.css";
import "preact-material-components/Radio/style.css";
import "preact-material-components/FormField/style.css";
import "preact-material-components/LayoutGrid/style.css";
import "mdn-polyfills/String.prototype.padStart";

class TimeSettings extends Component<Props, State> {
    state: State = {};

    onClickSave(): void {
        const config = this.state.config;
        if (config) {
            this.setState({ config: undefined });
            this.props.client.setTimeSettings(config).then(() => {
                route(Constants.routes.Home);
            });
        }
    }

    componentDidMount() {
        this.props.client
            .getTimeSettings()
            .then(config => this.setState({ config }));
        this.props.client
            .getTimeSettingsSettings()
            .then(settings => this.setState({ settings }));
    }

    render() {
        if (!this.state.config || !this.state.settings) {
            return (
                <div>
                    <LinearProgress indeterminate />
                </div>
            );
        }
        const content =
            this.state.config.mode == "internet"
                ? this.renderInternetSettings(
                    Number(this.state.config.timezone),
                    this.state.config.use_dst === "1"
                )
                : this.renderCustomSettings();

        return (
            <div class={style.timeSettings}>
                <h1>Time Settings</h1>
                <div>
                    {this.renderRadio("internet", "Use internet time")}
                    {this.renderRadio("custom", "Set custom time")}
                </div>
                {content}
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickSave()}>Save</Button>
                </div>
            </div>
        );
    }

    private renderRadio(type: TimeSettingsMode, label: string) {
        return (
            <FormField>
                <Radio
                    id={`timesettings-${type}`}
                    name="timesettings"
                    checked={this.state.config.mode == type}
                    onChange={e =>
                        this.setState({
                            config: { ...this.state.config, mode: type }
                        })
                    }
                />
                <h4>
                    <label htmlFor={`timesettings-${type}`}>{label}</label>
                </h4>
            </FormField>
        );
    }

    renderInternetSettings(
        selectedTimezone: number,
        useDaylightSaving: boolean
    ) {
        return (
            <div>
                <LayoutGrid>
                    <LayoutGrid.Inner>
                    {this.state.settings.zone_type.map((t,i) =>
                        this.renderTimeZones(t,i)
                    )}
                    </LayoutGrid.Inner>
                </LayoutGrid>
                <div>
                    <FormField>
                        <Checkbox
                            id="daylight-saving"
                            checked={useDaylightSaving}
                            onChange={e =>
                                this.setState({
                                    config: {
                                        ...this.state.config,
                                        // eslint-disable-next-line @typescript-eslint/camelcase
                                        use_dst: useDaylightSaving ? "0" : "1"
                                    }
                                })
                            }
                        />
                        <label htmlFor="daylight-saving">
                        enable Daylight saving
                        </label>
                    </FormField>
                </div>
            </div >
        );
    }

    renderTimeZones(type: string, index: number) {
        return (
            <FormField>
                <Radio
                    id={`timezone-${index}`}
                    name="timezone"
                    checked={Number(this.state.config.timezone) === index}
                    onChange={e =>
                        this.setState({
                            config: { ...this.state.config, timezone: index.toString() }
                        })
                    }
                />
                <label htmlFor={`timezone-${index}`}>{type}</label>
            </FormField>
        );
    }

    renderCustomSettings() {
        return (
            <div>
                <label htmlFor="ssid">Time</label>
                <TextField
                    id="time"
                    label="Time"
                    type="time"
                    helperText="hh:mm"
                    value={sanitizeTime(this.state.config.manual_time)}
                    onChange={e =>
                        this.setState({
                            config: {
                                ...this.state.config,
                                // eslint-disable-next-line @typescript-eslint/camelcase
                                manual_time: sanitizeTime(
                                    (e.target as HTMLInputElement).value
                                )
                            }
                        })
                    }
                    class={style.full}
                />
            </div>
        );
    }
}

interface State {
    config?: Config;
    settings?: TimeSettingsSettings;
}
interface Props {
    client: SWCClient;
}

export default TimeSettings;
