// We need to import the CSS so that webpack will load it.
// The MiniCssExtractPlugin is used to separate it out into
// its own CSS file.
import "../css/app.scss";

// webpack automatically bundles all modules in your
// entry points. Those entry points can be configured
// in "webpack.config.js".
//
// Import deps with the dep name or local files with a relative path, for example:
//
//     import {Socket} from "phoenix"
//     import socket from "./socket"
//
import "phoenix_html";
import { Socket } from "phoenix";
import NProgress from "nprogress";
import { LiveSocket } from "phoenix_live_view";
import { Network } from "vis-network";
import { DataSet } from "vis-data";

const links = (l) =>
  Object.keys(l).reduce((acc, x) => {
    if (l[x] !== undefined) {
      l[x].forEach((y) => acc.push({ from: x, to: y }));
      return acc;
    }
  }, []);

const nodes = (n) =>
  Object.keys(n).reduce((acc, x) => {
    acc.push({ id: x, label: x, group: 1 });
    return acc;
  }, []);

const data_transform = (d) => {
  return { nodes: nodes(d), edges: links(d) };
};

const data_loader = () => {
  const json = JSON.parse(document.getElementById("nodes").lastChild.data);
  console.log(data_transform(json.result));
  return Object.keys(json).length !== 0
    ? data_transform(json.result)
    : { nodes: [], edged: [] };
};

const DrawHook = {
  mounted() {
    this.handleMessages();
  },
  updated() {
    var newId = (Math.random() * 1e7).toString(32);
    this.n.add({ id: newId, label: "I'm new!" });

    this.network.stabilize();
    //    this.n.add({ id: "teg::prop7", label: "teg::prop7", group: 1 });
  },

  handleMessages() {
    //this.network.body.data.nodes.add([{ id: 6, label: "6", group: 1 }]);
    this.draw();
    // Do what you need to with messages
  },
  draw() {
    // create some nodes

    const data = data_loader();
    this.n = new DataSet();
    this.e = new DataSet();
    this.n.add(data.nodes);
    this.e.add(data.edges);
    var edges = this.e;
    this.e.on("*", function () {
      document.getElementById("edges").innerHTML = JSON.stringify(
        edges.get(),
        null,
        4
      );
    });
    var nodes = this.n;
    this.n.on("*", function () {
      document.getElementById("nodes").innerHTML = JSON.stringify(
        nodes.get(),
        null,
        4
      );
    });
    // create a network
    var container = document.getElementById("mynetwork");

    var options = {
      nodes: {
        shape: "dot",
        size: 16,
      },
      edges: {
        smooth: {
          type: "cubicBezier",
          roundness: 0.4,
        },
      },
      physics: {
        forceAtlas2Based: {
          gravitationalConstant: -26,
          centralGravity: 0.005,
          springLength: 230,
          springConstant: 0.18,
        },
        maxVelocity: 146,
        solver: "forceAtlas2Based",
        timestep: 0.35,
        stabilization: { iterations: 150 },
      },
    };
    this.network = new Network(
      container,
      { nodes: this.n, edges: this.e },
      options
    );
  },
};

window.addEventListener("nodes", ({ points }) => {
  console.log("fuck");
});

let csrfToken = document
  .querySelector("meta[name='csrf-token']")
  .getAttribute("content");

let liveSocket = new LiveSocket("/live", Socket, {
  params: { _csrf_token: csrfToken },
  hooks: { DrawHook: DrawHook },
});

// Show progress bar on live navigation and form submits
window.addEventListener("phx:page-loading-start", (info) => NProgress.start());
window.addEventListener("phx:page-loading-stop", (info) => NProgress.done());

// connect if there are any LiveViews on the page
liveSocket.connect();

// expose liveSocket on window for web console debug logs and latency simulation:
//liveSocket.enableDebug();
// >> liveSocket.enableLatencySim(1000)  // enabled for duration of browser session
// >> liveSocket.disableLatencySim()
window.liveSocket = liveSocket;
