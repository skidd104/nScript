const numscrpt = require('bindings')('numscrpt_core');
const fs = require('fs');

const data = fs.readFileSync('./datasets/ukCars.csv', 'utf8')
    .split('\n')
    .filter(line => line.trim() !== '')
    .map(line => line.split(','));


const body = data.slice(1);

let costs = body.map(r => parseFloat(r[21]));
let casualties = body.map(r => parseFloat(r[19]));

//Data Cleaning
//Check for dirty data 
if (numscrpt.isnan(costs).includes(true)) {
    const cleanCost = numscrpt.dropna(costs);
    const med = numscrpt.median(cleanCost);
    costs = numscrpt.fillna(costs, med);
}


// 4 Statistical Analysis
//
const report = {
    total_records: numscrpt.size(costs),
    mean_cost: numscrpt.mean(costs).toFixed(2),
    max_cost: numscrpt.max(costs),
    min_cost: numscrpt.min(costs),
    std_dev: numscrpt.std(costs).toFixed(2),
    variance: numscrpt.var(costs).toFixed(2),
    cost_casualty_corr: numscrpt.corr(casualties, costs).toFixed(4)
};

console.log("--- nScript EDA Report: UK Car Accidents ---");
console.table(report);


//Visualization
// 5. GRAPHING
const generateSVG = (xArr, yArr) => {
    const width = 600;
    const height = 400;
    const padding = 50;

    const minX = numscrpt.min(xArr), maxX = numscrpt.max(xArr);
    const minY = numscrpt.min(yArr), maxY = numscrpt.max(yArr);

    const points = xArr.map((x, i) => {
        const cx = padding + ((x - minX) / (maxX - minX)) * (width - 2 * padding);
        const cy = (height - padding) - ((yArr[i] - minY) / (maxY - minY)) * (height - 2 * padding);
        return `<circle cx="${cx}" cy="${cy}" r="4" fill="#007bff" opacity="0.6" />`;
    }).join('');

    const svg = `
    <svg width="${width}" height="${height}" viewBox="0 0 ${width} ${height}" xmlns="http://www.w3.org/2000/svg" style="background:#fff; border:1px solid #ccc">
        <text x="${width/2}" y="30" text-anchor="middle" font-weight="bold">Casualties vs Accidental Costs</text>
        ${points}
        <line x1="${padding}" y1="${height-padding}" x2="${width-padding}" y2="${height-padding}" stroke="black" />
        <line x1="${padding}" y1="${padding}" x2="${padding}" y2="${height-padding}" stroke="black" />
    </svg>`;

    fs.writeFileSync('accident_viz.svg', svg);
    console.log("Visualization saved as accident_viz.svg");
};

generateSVG(casualties, costs);
