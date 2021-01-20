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

let csrfToken = document
  .querySelector("meta[name='csrf-token']")
  .getAttribute("content");
let liveSocket = new LiveSocket("/live", Socket, {
  params: { _csrf_token: csrfToken },
});

// Show progress bar on live navigation and form submits
window.addEventListener("phx:page-loading-start", (info) => NProgress.start());
window.addEventListener("phx:page-loading-stop", (info) => NProgress.done());

// connect if there are any LiveViews on the page
liveSocket.connect();

// expose liveSocket on window for web console debug logs and latency simulation:
// >> liveSocket.enableDebug()
// >> liveSocket.enableLatencySim(1000)  // enabled for duration of browser session
// >> liveSocket.disableLatencySim()
window.liveSocket = liveSocket;

/*
var svg = d3.select("svg"),
  width = +svg.attr("width"),
  height = +svg.attr("height");

var simulation = d3
  .forceSimulation()
  .force(
    "link",
    d3.forceLink().id(function (d) {
      return d.id;
    })
  )
  //.force("charge", d3.forceManyBody().strength(-200))
  .force(
    "charge",
    d3.forceManyBody().strength(-200).theta(0.8).distanceMax(150)
  )
  // 		.force('collide', d3.forceCollide()
  //       .radius(d => 40)
  //       .iterations(2)
  //     )
  .force("center", d3.forceCenter(width / 2, height / 2));

const links = (l) =>
  Object.keys(l).reduce((acc, x) => {
    if (l[x] !== undefined) {
      l[x].forEach((y) => acc.push({ source: x, targe: y }));
      return acc;
    }
  }, []);

const nodes = (n) =>
  Object.keys(n).reduce((acc, x) => {
    acc.push({ id: x, group: 1 });
    return acc;
  }, []);

const data_transform = (d) => {
  return { nodes: nodes(d), links: links(d) };
};

const data_loader = () => {
  //  const json = JSON.parse(document.getElementById("nodes").lastChild.data);
  return Object.keys(json).length !== 0
    ? data_transform(json.result)
    : { nodes: [], links: [] };
};

const data = data_loader();

function run(graph) {
  graph.links.forEach(function (d) {
    //     d.source = d.source_id;
    //     d.target = d.target_id;
  });

  var link = svg
    .append("g")
    .style("stroke", "#aaa")
    .selectAll("line")
    .data(graph.links)
    .enter()
    .append("line");

  var node = svg
    .append("g")
    .attr("class", "nodes")
    .selectAll("circle")
    .data(graph.nodes)
    .enter()
    .append("circle")
    .attr("r", 2)
    .call(
      d3
        .drag()
        .on("start", dragstarted)
        .on("drag", dragged)
        .on("end", dragended)
    );

  var label = svg
    .append("g")
    .attr("class", "labels")
    .selectAll("text")
    .data(graph.nodes)
    .enter()
    .append("text")
    .attr("class", "label")
    .text(function (d) {
      return d.id;
    });

  simulation.nodes(graph.nodes).on("tick", ticked);

  simulation.force("link").links(graph.links);

  function ticked() {
    link
      .attr("x1", function (d) {
        return d.source.x;
      })
      .attr("y1", function (d) {
        return d.source.y;
      })
      .attr("x2", function (d) {
        return d.target.x;
      })
      .attr("y2", function (d) {
        return d.target.y;
      });

    node
      .attr("r", 16)
      .style("fill", "#efefef")
      .style("stroke", "#424242")
      .style("stroke-width", "1px")
      .attr("cx", function (d) {
        return d.x + 5;
      })
      .attr("cy", function (d) {
        return d.y - 3;
      });

    label
      .attr("x", function (d) {
        return d.x;
      })
      .attr("y", function (d) {
        return d.y;
      })
      .style("font-size", "10px")
      .style("fill", "#333");
  }
}

function dragstarted(d) {
  if (!d3.event.active) simulation.alphaTarget(0.3).restart();
  d.fx = d.x;
  d.fy = d.y;
  //  simulation.fix(d);
}

function dragged(d) {
  d.fx = d3.event.x;
  d.fy = d3.event.y;
  //  simulation.fix(d, d3.event.x, d3.event.y);
}

function dragended(d) {
  d.fx = d3.event.x;
  d.fy = d3.event.y;
  if (!d3.event.active) simulation.alphaTarget(0);

  //simulation.unfix(d);
}

run(data);
*/
