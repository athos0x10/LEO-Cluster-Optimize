import pandas as pd
import geopandas as gpd
import matplotlib.pyplot as plt
import contextily as ctx
import os
from shapely.geometry import Point


"""
PREREQUIS

pip install pandas geopandas matplotlib contextily shapely


Tout en bas du fichier:
Modifiez ces deux variables pour tester différentes visualisations

AFFICHER_CLUSTERS = False  # Sur False, les cercles disparaissent
AFFICHER_UTILISATEURS = True # Sur True, seuls les points s'affichent

"""

def plot_clusters_static_map(csv_clusters, output_image_path, csv_users=None, show_clusters=True, show_users=False, bounds=None):
    print(f"Chargement des clusters depuis {csv_clusters}...")
    
    # 1. Lecture du CSV des clusters
    df_clusters = pd.read_csv(csv_clusters)
    
    # 2. Création de la géométrie des centres (WGS84)
    geometry_c = [Point(xy) for xy in zip(df_clusters['center_lon'], df_clusters['center_lat'])]
    gdf_clusters = gpd.GeoDataFrame(df_clusters, geometry=geometry_c, crs="EPSG:4326")
    
    # 3. Filtrage par zone
    if bounds:
        minx, miny, maxx, maxy = bounds
        gdf_clusters = gdf_clusters.cx[minx:maxx, miny:maxy]
        if gdf_clusters.empty:
            print("Aucun cluster dans cette zone. Fin du script.")
            return

    # 4. Projection en Mercator (pour obtenir des mètres)
    gdf_clusters_mercator = gdf_clusters.to_crs(epsg=3857)
    gdf_clusters_mercator['geometry'] = gdf_clusters_mercator.geometry.buffer(45000)
    
    # --- PRÉPARATION DES COULEURS ---
    # Calcul des limites du gradient basé sur les clusters (même si on ne les affiche pas)
    vmin = gdf_clusters_mercator['current_load'].min()
    vmax = gdf_clusters_mercator['current_load'].max()
    
    # 5. Configuration du tracé
    fig, ax = plt.subplots(figsize=(12, 12))
    
    # 6. Affichage des clusters (Cercles) SI activé
    if show_clusters:
        gdf_clusters_mercator.plot(
            ax=ax, 
            column='current_load', 
            cmap='YlOrRd', 
            vmin=vmin, vmax=vmax,
            alpha=0.4, 
            edgecolor='black', 
            linewidth=0.5,
            legend=not show_users, # Évite d'avoir la légende en double si les deux sont affichés
            legend_kwds={'label': "Débit Cumulé (current_load)", 'orientation': "vertical"} if not show_users else None
        )
    
    # 7. Affichage des Utilisateurs (Points) SI activé
    if show_users and csv_users:
        print(f"Chargement des utilisateurs depuis {csv_users}...")
        df_users = pd.read_csv(csv_users)
        
        # Déduction de l'ID à partir du numéro de ligne
        df_users['id_user'] = df_users.index + 1 
        
        # Création du dictionnaire de correspondance {user_id: current_load}
        dict_user_load = {}
        for idx, row in gdf_clusters.iterrows():
            if pd.isna(row['users_id']): continue
            u_ids = str(row['users_id']).split(';')
            for uid in u_ids:
                try:
                    dict_user_load[int(uid)] = row['current_load']
                except ValueError:
                    pass
        
        # Application de la charge à chaque utilisateur
        df_users['cluster_load'] = df_users['id_user'].map(dict_user_load)
        df_users_filtered = df_users.dropna(subset=['cluster_load'])
        
        if not df_users_filtered.empty:
            geom_u = [Point(xy) for xy in zip(df_users_filtered['LON'], df_users_filtered['LAT'])]
            gdf_users = gpd.GeoDataFrame(df_users_filtered, geometry=geom_u, crs="EPSG:4326")
            gdf_users_mercator = gdf_users.to_crs(epsg=3857)
            
            # Tracé des points utilisateurs
            gdf_users_mercator.plot(
                ax=ax,
                column='cluster_load',
                cmap='YlOrRd',
                vmin=vmin, vmax=vmax,
                markersize=8,
                edgecolor='black',
                linewidth=0.3,
                zorder=5,
                legend=True, # On met la légende ici pour qu'elle soit associée aux points
                legend_kwds={'label': "Débit Cumulé du Cluster Parent", 'orientation': "vertical"}
            )
        else:
            print("Aucun utilisateur à afficher dans cette zone.")

    # 8. Ajout du fond de carte
    print("Téléchargement du fond de carte...")
    ctx.add_basemap(ax, source=ctx.providers.CartoDB.Positron)
    
    ax.set_axis_off()
    
    # Gestion dynamique du titre
    titre = "Répartition du Réseau Satellite"
    if show_clusters and show_users: titre = "Clusters (45km) et Utilisateurs"
    elif show_clusters: titre = "Faisceaux des Clusters (Rayon 45km)"
    elif show_users: titre = "Utilisateurs (Couleur = Charge du Cluster)"
    plt.title(titre, fontsize=16)
    
    # 9. Sauvegarde
    plt.tight_layout()
    plt.savefig(output_image_path, dpi=300, bbox_inches='tight')
    print(f"Carte sauvegardée avec succès sous : {output_image_path}")
    plt.close()

# --- Exécution du script ---
if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    fichier_csv_clusters = os.path.join(script_dir, "../data/test.csv")
    fichier_csv_users = os.path.join(script_dir, "../data/users.csv")
    image_sortie = os.path.join(script_dir, "carte_utilisateurs_france_clusters.png")
    
    # --- TABLEAU DE BORD ---
    # Modifiez ces deux variables pour tester différentes visualisations
    AFFICHER_CLUSTERS = True  # Sur False, les cercles disparaissent
    AFFICHER_UTILISATEURS = False # Sur True, seuls les points s'affichent
    
    # Bounding Box: France
    bounds_france = (-5.5, 41.3, 9.6, 51.1) 
    
    plot_clusters_static_map(
        csv_clusters=fichier_csv_clusters, 
        output_image_path=image_sortie, 
        csv_users=fichier_csv_users,
        show_clusters=AFFICHER_CLUSTERS,
        show_users=AFFICHER_UTILISATEURS,
        bounds=bounds_france
    )
