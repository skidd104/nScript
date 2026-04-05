const numscrpt = require('bindings')('numscrpt_core');
const fs = require('fs');
const { performance } = require('perf_hooks');

// --- 1. LOAD & CLEAN DATA ---
const raw = fs.readFileSync('./datasets/ukCars.csv', 'utf8')
    .split('\n')
    .filter(line => line.trim() !== '' && line.includes(','))
    .map(line => line.split(','));

const body = raw.slice(1);

// Extract Columns
let costs = body.map(r => parseFloat(r[21]));
let casualties = body.map(r => parseFloat(r[19]));
let vehicles = body.map(r => parseFloat(r[20]));

// --- 2. CALCULATE METRICS (WITH PERFORMANCE TIMER) ---
// Start timer just before nScript calls
const start = performance.now();

// Data Integrity Check with numscrpt
if (numscrpt.isnan(costs).includes(true)) {
    costs = numscrpt.fillna(costs, numscrpt.median(numscrpt.dropna(costs)));
}

const totalRecords = numscrpt.size(costs);
const avgCost = numscrpt.mean(costs);
const costStd = numscrpt.std(costs);
const maxCost = numscrpt.max(costs);
const correlation = numscrpt.corr(casualties, costs);

const uniqueCas = [...new Set(casualties)].sort((a, b) => a - b);
const avgCostByCas = uniqueCas.map(c => {
    const filtered = body.filter(r => parseFloat(r[19]) === c).map(r => parseFloat(r[21]));
    return numscrpt.mean(filtered);
});

const end = performance.now();
const calcTime = (end - start).toFixed(4); // Time in milliseconds

// --- 3. GENERATE THE DASHBOARD ---
const html = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>nScript EDA Dashboard</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body { font-family: 'Segoe UI', sans-serif; background: #f0f2f5; margin: 0; padding: 40px; }
        .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(180px, 1fr)); gap: 20px; margin-bottom: 30px; }
        .card { background: white; padding: 20px; border-radius: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.05); text-align: center; }
        .card h3 { margin: 0; color: #666; font-size: 0.85rem; text-transform: uppercase; letter-spacing: 1px; }
        .card p { margin: 10px 0 0; font-size: 1.5rem; font-weight: bold; color: #4FC08D; }
        .chart-container { background: white; padding: 30px; border-radius: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.05); }
        .speed-badge { color: #3498db !important; } /* Distinct color for speed */
    </style>
</head>
<body>
    <h1>UK Accidents: nScript EDA Report</h1>
    
    <div class="grid">
        <div class="card"><h3>Total Records</h3><p>${totalRecords}</p></div>
        <div class="card"><h3>Mean Cost</h3><p>£${avgCost.toFixed(2)}</p></div>
        <div class="card"><h3>Max Cost</h3><p>£${maxCost.toFixed(2)}</p></div>
        <div class="card"><h3>Correlation</h3><p>${correlation.toFixed(4)}</p></div>
        <div class="card"><h3>Calculation Time</h3><p class="speed-badge">${calcTime} ms</p></div>
    </div>

    <div class="chart-container">
        <canvas id="mainChart"></canvas>
    </div>

    <script>
        new Chart(document.getElementById('mainChart'), {
            type: 'line',
            data: {
                labels: ${JSON.stringify(uniqueCas)},
                datasets: [{
                    label: 'Avg Cost by Number of Casualties',
                    data: ${JSON.stringify(avgCostByCas)},
                    borderColor: '#4FC08D',
                    backgroundColor: 'rgba(79, 192, 141, 0.1)',
                    fill: true,
                    tension: 0.4,
                    pointRadius: 6,
                    pointBackgroundColor: '#fff',
                    pointBorderColor: '#4FC08D',
                    borderWidth: 3
                }]
            },
            options: {
                responsive: true,
                scales: {
                    y: { title: { display: true, text: 'Cost (£)' }, grid: { color: '#eee' } },
                    x: { title: { display: true, text: 'Casualties' }, grid: { display: false } }
                }
            }
        });
    </script>
</body>
</html>
`;

fs.writeFileSync('nScript_Dashboard.html', html);
console.log(`
---------------------------------------
Records Scanned  : ${totalRecords}
Calculation Time : ${calcTime} ms (Native C++)
Output File      : nScript_Dashboard.html
---------------------------------------
`);
