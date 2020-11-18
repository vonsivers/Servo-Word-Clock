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
    TimeSettingsMode
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
    }

    render() {
        if (!this.state.config) {
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
                        <LayoutGrid.Cell phoneCols={2}>
                            {this.renderTimeZones(0, selectedTimezone)}
                        </LayoutGrid.Cell>
                        <LayoutGrid.Cell phoneCols={2}>
                            {this.renderTimeZones(1, selectedTimezone)}
                        </LayoutGrid.Cell>
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
            </div>
        );
    }

    renderTimeZones(offset: number, selectedTimezone: number) {
        const result = [];
        for (let i = 0; i < 12; i++) {
            const num = i * 2 + offset;
            result.push(
                <FormField>
                    <Radio
                        id={`timezone-${num}`}
                        name="timezone"
                        checked={num === selectedTimezone}
                        onChange={e =>
                            this.setState({
                                config: {
                                    ...this.state.config,
                                    timezone: num.toString()
                                }
                            })
                        }
                    />
                    <label htmlFor={`timezone-${num}`}>
                        GTM +{num.toString().padStart(2, "0")}
                    </label>
                </FormField>
            );
            result.push(<br />);
        }
        return result;
    }

    renderCustomSettings() {
        return (
            <div>
                <label htmlFor="ssid">Time</label>
                <TextField
                    id="time"
                    label="Time"
                    type="time"
                    helperText="hh:mm:ss"
                    step="1"
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
}
interface Props {
    client: SWCClient;
}

export default TimeSettings;
