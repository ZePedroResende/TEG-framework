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
      l[x].forEach((y) => acc.push({ from: x, to: y, id: x + "-" + y }));
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
  return Object.keys(json).length !== 0
    ? data_transform(json.result)
    : { nodes: [], edges: [] };
};

const DrawHook = {
  mounted() {
    this.draw();

    this.handleEvent("enqueue", (points) => {
      var result = points["result"];
      var mydiv = document.getElementById("events");
      var row = mydiv.insertRow(0);
      var cell1 = row.insertCell(0);
      var cell2 = row.insertCell(1);
      var cell3 = row.insertCell(2);
      var cell4 = row.insertCell(3);
      var cell5 = row.insertCell(4);
      cell1.innerHTML = "enqueue";
      cell2.innerHTML = result["function"];
      cell5.innerHTML = result["data_id"];
      var nodeID = result["function"];
      if (nodeID) {
        var clickedNode = this.n.get(nodeID);
        clickedNode.color = {
          border: "#000000",
          background: "#ff6604",
          highlight: {
            border: "#2B7CE9",
            background: "#D2E5FF",
          },
        };
        this.n.update(clickedNode);
      }
    });

    this.handleEvent("calculate", (points) => {
      var result = points["result"];
      var mydiv = document.getElementById("events");
      var row = mydiv.insertRow(0);
      var cell1 = row.insertCell(0);
      var cell2 = row.insertCell(1);
      var cell3 = row.insertCell(2);
      var cell4 = row.insertCell(3);
      var cell5 = row.insertCell(4);
      cell1.innerHTML = "calculate";
      cell2.innerHTML = result["function"];
      cell4.innerHTML = result["thread_id"];
      cell5.innerHTML = result["data_id"];

      var nodeID = result["function"];
      if (nodeID) {
        var clickedNode = this.n.get(nodeID);
        clickedNode.color = {
          border: "#000000",
          background: "#ffeb3c",
          highlight: {
            border: "#2B7CE9",
            background: "#D2E5FF",
          },
        };
        this.n.update(clickedNode);
      }
    });

    this.handleEvent("result", (points) => {
      var result = points["result"];
      var mydiv = document.getElementById("events");
      var row = mydiv.insertRow(0);
      var cell1 = row.insertCell(0);
      var cell2 = row.insertCell(1);
      var cell3 = row.insertCell(2);
      var cell4 = row.insertCell(3);
      var cell5 = row.insertCell(4);
      cell1.innerHTML = "result";
      cell2.innerHTML = result["function"];
      cell3.innerHTML = result["result"];
      cell4.innerHTML = result["thread_id"];
      cell5.innerHTML = result["data_id"];

      var nodeID = result["function"];
      if (nodeID) {
        var clickedNode = this.n.get(nodeID);
        clickedNode.color = {
          border: "#000000",
          background: "#6dca12",
          highlight: {
            border: "#2B7CE9",
            background: "#D2E5FF",
          },
        };
        this.n.update(clickedNode);

        this.e.update({
          id: result["function"] + "-" + result["result"],
          color: { color: "#6dca12" },
        });
      }
    });

    this.handleEvent("finish", (points) => {
      var result = points["result"];
      var mydiv = document.getElementById("events");
      var row = mydiv.insertRow(0);
      var cell1 = row.insertCell(0);
      var cell2 = row.insertCell(1);
      var cell3 = row.insertCell(2);
      var cell4 = row.insertCell(3);
      var cell5 = row.insertCell(4);
      cell1.innerHTML = "finish";
      cell2.innerHTML = result["function"];
      cell5.innerHTML = result["data_id"];

      var nodeID = result["function"];
      this.draw();
    });
  },
  updated() {
    var container = data_loader();

    const data = data_loader();

    console.log(data);
    this.n.add(data.nodes);
    this.e.add(data.edges);
  },

  draw() {
    // create some nodes

    const data = data_loader();
    this.n = new DataSet();
    this.e = new DataSet();
    this.n.add(data.nodes);
    this.e.add(data.edges);
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
        color: {
          inherit: false,
        },
        arrows: {
          to: {
            enabled: true,
          },
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
      layout: {
        hierarchical: {
          sortMethod: "directed",
        },
      },
    };
    this.network = new Network(
      container,
      { nodes: this.n, edges: this.e },
      options
    );
  },
};

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
