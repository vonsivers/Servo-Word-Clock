import { FunctionalComponent, h } from "preact";
import Card from "preact-material-components/Card";
import "preact-material-components/Card/style.css";
import "preact-material-components/Button/style.css";
import "preact-material-components/Icon/style.css";
import * as style from "./style.css";
import { route } from "preact-router";
import Constants from "../../Constants";
import Icon from "preact-material-components/Icon";

const renderCard = (
    title: string,
    description: string,
    icon: string,
    routePath: string
) => (
    <Card class={style.card}>
        <div class={style.cardHeader}>
            <h2 class=" mdc-typography--title">
                <Icon class={style.icon}>{icon}</Icon>
                {title}
            </h2>
        </div>
        <div class={style.cardBody}>{description}</div>
        <Card.Actions class={style.contentEnd}>
            <Card.ActionButtons>
                <Card.ActionButton
                    onClick={() => {
                        route(routePath);
                    }}
                >
                    OK
                </Card.ActionButton>
            </Card.ActionButtons>
        </Card.Actions>
    </Card>
);

const Home: FunctionalComponent = () => {
    return (
        <div class={style.home}>
            {renderCard(
                `Wifi`,
                `Select your local WiFi network`,
                `wifi`,
                Constants.routes.Wifi
            )}
            {renderCard(
                `Time Settings`,
                `Enter your local timezone or set the time manually, if your clock is not connected to the internet or cannot synchronize`,
                `timelapse`,
                Constants.routes.TimeSettings
            )}
            {renderCard(
                `Display effects`,
                `Change several options on how the clock displays time`,
                `grid_on`,
                Constants.routes.Display
            )}
            {renderCard(
                `Night mode`,
                `Either switch off the servos or the entire clock for certain periods`,
                `notifications_paused`,
                Constants.routes.NightMode
            )}
        </div>
    );
};

export default Home;
