import { FunctionalComponent, h, Component } from "preact";
import * as style from "./style.css";
import Button from "preact-material-components/Button";
import Slider from "preact-material-components/Slider";
import Select from "preact-material-components/Select";
import LinearProgress from "preact-material-components/LinearProgress";
import "preact-material-components/LinearProgress/style.css";
import "preact-material-components/List/style.css";
import "preact-material-components/Menu/style.css";
import "preact-material-components/Select/style.css";
import "preact-material-components/Slider/style.css";
import "preact-material-components/Button/style.css";
import Constants from "../../Constants";
import { route } from "preact-router";
import {
    SWCClient,
    DisplayEffectsSettings,
    DisplayEffects as Config
} from "../../domain/SWCClient";

class Display extends Component<Props, State> {
    onClickSave(): void {
        const config = this.state.config;
        if (config) {
            this.setState({ config: undefined });
            this.props.client.setDisplayEffects(config).then(() => {
                route(Constants.routes.Home);
            });
        }
    }
    componentDidMount() {
        this.props.client
            .getDisplayEffects()
            .then(config => this.setState({ config }));
        this.props.client
            .getDisplayEffectsSettings()
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
        return (
            <div class={style.display}>
                <h1>Display Effects</h1>
                <div>
                    <label htmlFor="brightness">Brightness</label>
                    <Slider id="brightness" step={1} value={Number(this.state.config.brightness)} min={50} max={255} onChange={e =>{e.detail.value && this.setState({config:{...this.state.config,brightness:e.detail.value}})} } />
                </div>
                {this.renderSelect(
                    "effect_hour",
                    "Hour effect",
                    this.state.settings.effect_type
                )}
                {this.renderSelect(
                    "effect_5minute",
                    "5 minute effect",
                    this.state.settings.effect_type
                )}
                {this.renderSelect(
                    "color_mode_dot",
                    "Dot color mode",
                    this.state.settings.color_mode_dot_type
                )}
                {this.renderColor("color_dot", "Dot color")}
                {this.renderSelect(
                    "color_mode_word",
                    "Word color mode",
                    this.state.settings.color_mode_word_type
                )}
                {this.renderColor("color_word", "Word color")}
                {this.renderSelect(
                    "color_mode_background",
                    "Background color mode",
                    this.state.settings.color_mode_background_type
                )}
                {this.renderColor("color_background", "Background color")}
                <div class={style.textRight}>
                    <Button onClick={() => this.onClickSave()}>Save</Button>
                </div>
            </div>
        );
    }

    private renderColor(fieldName: keyof Config, label: string) {
        return (
            <div>
                <label htmlFor={fieldName}>{label}</label>
                <div class={style.control}>
                    <input
                        id={fieldName}
                        type="color"
                        value={this.state.config[fieldName]}
                        onChange={e =>
                            this.setState({
                                config: {
                                    ...this.state.config,
                                    [fieldName]: (e.target as HTMLInputElement)
                                        .value
                                }
                            })
                        }
                    />
                </div>
            </div>
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
}

interface Props {
    client: SWCClient;
}
interface State {
    config?: Config;
    settings?: DisplayEffectsSettings;
}

export default Display;
