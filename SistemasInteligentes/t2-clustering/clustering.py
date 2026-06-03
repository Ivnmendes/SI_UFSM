import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans, AgglomerativeClustering, DBSCAN
from sklearn.metrics import silhouette_score, davies_bouldin_score, calinski_harabasz_score
import os

os.makedirs('images', exist_ok=True)

from scipy import stats

df = pd.read_csv('heart-failure-prediction/heart.csv')

df = df[(np.abs(stats.zscore(df.select_dtypes(include=['number']))) < 3).all(axis=1)]

desc = df.describe()
desc.to_csv('images/desc_stats.csv')

df.hist(figsize=(10, 8), bins=20)
plt.tight_layout()
plt.savefig('images/histograms.png')
plt.close()

X = df.drop('HeartDisease', axis=1)
y = df['HeartDisease']

numeric_features = X.select_dtypes(include=['int64', 'float64']).columns
categorical_features = X.select_dtypes(include=['object']).columns

preprocessor = ColumnTransformer(
    transformers=[
        ('num', StandardScaler(), numeric_features),
        ('cat', OneHotEncoder(sparse_output=False, drop='first'), categorical_features)
    ])

X_scaled = preprocessor.fit_transform(X)

feature_names = list(numeric_features) + list(preprocessor.named_transformers_['cat'].get_feature_names_out(categorical_features))
df_processed = pd.DataFrame(X_scaled, columns=feature_names)
df_processed['HeartDisease'] = y.values

plt.figure(figsize=(12, 10))
sns.heatmap(df_processed.corr(), annot=False, cmap='coolwarm')
plt.title('Correlation Matrix')
plt.tight_layout()
plt.savefig('images/correlation.png')
plt.close()

pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

results = []

for k in [2, 3, 4]:
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    labels = kmeans.fit_predict(X_scaled)
    results.append({
        'Algorithm': 'K-Means',
        'Params': f'k={k}',
        'Silhouette': silhouette_score(X_scaled, labels),
        'Davies-Bouldin': davies_bouldin_score(X_scaled, labels),
        'Calinski-Harabasz': calinski_harabasz_score(X_scaled, labels)
    })
    
    if k == 2:
        plt.scatter(X_pca[:, 0], X_pca[:, 1], c=labels, cmap='viridis', alpha=0.6)
        plt.title('K-Means (k=2) PCA')
        plt.savefig('images/kmeans_pca.png')
        plt.close()

for linkage in ['ward', 'complete', 'average']:
    agg = AgglomerativeClustering(n_clusters=2, linkage=linkage)
    labels = agg.fit_predict(X_scaled)
    results.append({
        'Algorithm': 'Agglomerative',
        'Params': f'linkage={linkage}',
        'Silhouette': silhouette_score(X_scaled, labels),
        'Davies-Bouldin': davies_bouldin_score(X_scaled, labels),
        'Calinski-Harabasz': calinski_harabasz_score(X_scaled, labels)
    })

pca_dbscan = PCA(n_components=3)
X_reduced = pca_dbscan.fit_transform(X_scaled)

for eps in [1.5, 2.0, 2.5]:
    dbscan = DBSCAN(eps=eps, min_samples=5)
    labels = dbscan.fit_predict(X_reduced)
    if len(set(labels)) > 1:
        results.append({
            'Algorithm': 'DBSCAN',
            'Params': f'eps={eps}',
            'Silhouette': silhouette_score(X_scaled, labels),
            'Davies-Bouldin': davies_bouldin_score(X_scaled, labels),
            'Calinski-Harabasz': calinski_harabasz_score(X_scaled, labels)
        })

results_df = pd.DataFrame(results)
results_df.to_csv('images/clustering_results.csv', index=False)
print(results_df)

plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y, cmap='coolwarm', alpha=0.6)
plt.title('Ground Truth (HeartDisease) PCA')
plt.savefig('images/ground_truth_pca.png')
plt.close()
