import { h, Component } from "preact";
import Constants from "../../Constants";
import TopAppBar from "preact-material-components/TopAppBar";
import Drawer from "preact-material-components/Drawer";
import List from "preact-material-components/List";
import "preact-material-components/Drawer/style.css";
import "preact-material-components/List/style.css";
import "preact-material-components/TopAppBar/style.css";
import { route } from "preact-router";
import * as style from "./style.css";

interface State {
    isDrawerOpen: boolean;
}

interface Props {
    currentRoute: string;
    isLoggedIn: boolean;
}

class Header extends Component<Props, State> {
    constructor() {
        super();
        this.state = {
            isDrawerOpen: false
        };
    }
    route(url: string) {
        route(url);
        this.setState({ isDrawerOpen: false });
    }

    render() {
        return (
            <div>
                <TopAppBar class={style.header} onNav={null}>
                    <TopAppBar.Row>
                        <TopAppBar.Section align-start>
                            <TopAppBar.Icon
                                class={style.icon}
                                onClick={() => {
                                    this.setState({
                                        isDrawerOpen: !this.state.isDrawerOpen
                                    });
                                }}
                            >
                                menu
                            </TopAppBar.Icon>
                            <TopAppBar.Title>Servo Word Clock</TopAppBar.Title>
                        </TopAppBar.Section>
                    </TopAppBar.Row>
                </TopAppBar>
                <Drawer
                    modal
                    open={this.state.isDrawerOpen && this.props.isLoggedIn}
                    onClose={() => {
                        this.setState({ isDrawerOpen: false });
                    }}
                >
                    <Drawer.DrawerContent>
                        {this.renderDrawerItem(
                            `Home`,
                            `home`,
                            Constants.routes.Home
                        )}
                        {this.renderDrawerItem(
                            `Wifi`,
                            `wifi`,
                            Constants.routes.Wifi
                        )}
                        {this.renderDrawerItem(
                            `Time Settings`,
                            `timelapse`,
                            Constants.routes.TimeSettings
                        )}
                        {this.renderDrawerItem(
                            `Display effects`,
                            `grid_on`,
                            Constants.routes.Display
                        )}
                        {this.renderDrawerItem(
                            `Night mode`,
                            `notifications_paused`,
                            Constants.routes.NightMode
                        )}
                        {this.renderDrawerItem(
                            `Change password`,
                            `vpn_key`,
                            Constants.routes.ChangePassword
                        )}
                    </Drawer.DrawerContent>
                </Drawer>
            </div>
        );
    }

    private renderDrawerItem(title: string, icon: string, routePath: string) {
        return (
            <Drawer.DrawerItem
                class={style.drawer}
                selected={this.props.currentRoute === routePath}
                onClick={() => {
                    this.route(routePath);
                }}
            >
                <List.ItemGraphic>{icon}</List.ItemGraphic>
                {title}
            </Drawer.DrawerItem>
        );
    }
}

export default Header;
