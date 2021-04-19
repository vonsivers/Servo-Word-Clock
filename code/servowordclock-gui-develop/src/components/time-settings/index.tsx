import { h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import TextField from "preact-material-components/TextField";
import Select from "preact-material-components/Select";
import "preact-material-components/Button/style.css";
import "preact-material-components/TextField/style.css";
import Constants, { sanitizeTime, sanitizeDate } from "../../Constants";
import { route } from "preact-router";
import {
    SWCClient,
    TimeSettings as Config,
    TimeSettingsMode,
    TimeSettingsSettings
} from "../../domain/SWCClient";
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
                ? this.renderInternetSettings()
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
    ) {
        return (
            <div>
                {this.renderSelect(
                    "timezone",
                    "Timezone",
                    this.state.settings.zone_type
                )}
            </div >
        );
    }

    private renderSelect(
        fieldName: keyof Config,
        label: string,
        options: string[]
    ) {
        return (
            <div>
                <label htmlFor={fieldName}>{label}</label>
                <div>
                    <Select
                        id={fieldName}
                        hintText={label}
                        class={style.control}
                        value={Number(this.state.config[fieldName])}
                        onChange={e =>
                            this.setState({
                                config: {
                                    ...this.state.config,
                                    [fieldName]: (e.target as HTMLSelectElement)
                                        .value
                                }
                            })
                        }
                    >
                        {options.map((o, i) => (
                            <Select.Item key={i} value={i} selected={i===Number(this.state.config[fieldName])}>
                                {o}
                            </Select.Item>
                        ))}
                    </Select>
                </div>
            </div>
        );
    }

    renderCustomSettings() {
        return (
            <div>
                <LayoutGrid>
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
                </LayoutGrid>
                <LayoutGrid>
                <label htmlFor="ssid">Date</label>
                <TextField
                    id="date"
                    label="Date"
                    type="date"
                    helperText="dd.mm.yyyy"
                    value={sanitizeDate(this.state.config.manual_date)}
                    onChange={e =>
                        this.setState({
                            config: {
                                ...this.state.config,
                                // eslint-disable-next-line @typescript-eslint/camelcase
                                manual_date: sanitizeDate((e.target as HTMLInputElement).value)
                            }
                        })
                    }
                    class={style.full}
                />
                </LayoutGrid>
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
