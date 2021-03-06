import { h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import FormField from "preact-material-components/FormField";
import TextField from "preact-material-components/TextField";
import LayoutGrid from "preact-material-components/LayoutGrid";
import LinearProgress from "preact-material-components/LinearProgress";
import "preact-material-components/LinearProgress/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/FormField/style.css";
import "preact-material-components/TextField/style.css";
import "preact-material-components/Radio/style.css";
import "preact-material-components/LayoutGrid/style.css";
import Constants, { sanitizeTime } from "../../Constants";
import { route } from "preact-router";
import {
    SWCClient,
    NightModeSettings,
    NightMode as Config
} from "../../domain/SWCClient";
import Radio from "preact-material-components/Radio";

class NightMode extends Component<Props, State> {
    onClickSave(): void {
        const config = this.state.config;
        if (config) {
            this.setState({ config: undefined });
            this.props.client.setNightMode(config).then(() => {
                route(Constants.routes.Home);
            });
        }
    }
    componentDidMount() {
        this.props.client
            .getNightMode()
            .then(config => this.setState({ config }));
        this.props.client
            .getNightModeSettings()
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
            Number(this.state.config.mode) === 0 ? null : this.renderContent();
        return (
            <div class={style.nightMode}>
                <h1>Night Mode</h1>
                <div>
                    {this.renderRadio("disabled",0)}
                    {this.state.settings.mode_type.map((t,i) =>
                        this.renderRadio(t,i+1)
                    )}
                </div>
                {content}
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickSave()}>Save</Button>
                </div>
            </div>
        );
    }

    private renderRadio(type: string, index: Number) {
        const cssType = type.replace(" ", "-");
        return (
            <FormField>
                <Radio
                    id={`nightmode-${cssType}`}
                    name="nightmode"
                    checked={Number(this.state.config.mode) === index}
                    onChange={e =>
                        this.setState({
                            config: { ...this.state.config, mode: index.toString() }
                        })
                    }
                />
                <label htmlFor={`nightmode-${cssType}`}>{type}</label>
            </FormField>
        );
    }

    private renderContent() {
        return (
            <div>
                <h4>Weekdays</h4>
                <LayoutGrid>
                    <LayoutGrid.Inner>
                        {this.renderTimeFieldCell(
                            "weekday_start",
                            "Start time"
                        )}
                        {this.renderTimeFieldCell("weekday_end", "End time")}
                    </LayoutGrid.Inner>
                </LayoutGrid>
                <h4>Weekends</h4>
                <LayoutGrid>
                    <LayoutGrid.Inner>
                        {this.renderTimeFieldCell(
                            "weekend_start",
                            "Start time"
                        )}
                        {this.renderTimeFieldCell("weekend_end", "End time")}
                    </LayoutGrid.Inner>
                </LayoutGrid>
            </div>
        );
    }

    private renderTimeFieldCell(fieldName: keyof Config, label: string) {
        return (
            <LayoutGrid.Cell phoneCols={2}>
                <label htmlFor={fieldName}>{label}</label>
                <TextField
                    id={fieldName}
                    label={label}
                    type="time"
                    helperText="hh:mm"
                    class={style.full}
                    value={sanitizeTime(this.state.config[fieldName])}
                    onChange={e =>
                        this.setState({
                            config: {
                                ...this.state.config,
                                [fieldName]: sanitizeTime(
                                    (e.target as HTMLInputElement).value
                                )
                            }
                        })
                    }
                />
            </LayoutGrid.Cell>
        );
    }
}

interface State {
    config?: Config;
    settings?: NightModeSettings;
}
interface Props {
    client: SWCClient;
}

export default NightMode;
